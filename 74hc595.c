#include "../main.h"



/************************************************************************/
/* 功能：led_data是3个数据，grid_data是8个数据
 * 描述：数组前面的数据先传入，下标大的数据后传入
 * 形参：
 * 返回：无    */
/************************************************************************/
void hc595_out(u8 *led_data,u8 *grid_data)
{
  	u8 i,j,grid,led;

	SH_CP_L;
	ST_CP_L;
	for(i=0; i<8; i++)
	{
	   	grid = *(grid_data + i);
	 	if(i>=5)		led = *(led_data + i-5);	//LED数据在最后3个数据时传入				
		
		for(j=0; j<8; j++)
		{
			if((grid&0x80))		GRID_DS_H;			//先输出的是高位
			else 				GRID_DS_L;
			grid<<=1;
			
			if(i>=5)							//LED只有3个
			{
				if((led&0x80))		LED_DS_H;
				else				LED_DS_L;	
				led<<=1;
			}	
			
			SH_CP_H;
			SH_CP_L;		
		}
	}
	ST_CP_H;			//输出
}