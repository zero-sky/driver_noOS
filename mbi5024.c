/************************************************************************/
/* 名称：MBI5020/5024/5026等16位恒流芯片驱动
 * 描述：
 * 编写：邹应龙
 * 修改：2016-11-26
 * 缘由：舒华5517*/
/************************************************************************/
#include "../main.h"
 /************************************************************************/
/* 功能：MBI 传输数据
 * 描述：
 * 形参：数据数组开始地址(16bit)，芯片级联数目(也是数组长度)
 * 返回：无    */
/************************************************************************/

void mbi_out(u16 *buf,s8 cnt)
{
	u8 high,low;
	// MBI_OE_H;
	MBI_LE_L;
	for (s8 i=0; i<cnt; i++)
	{
		high = (u8)((*(buf+i)>>8));
		low = (u8)(*(buf+i));

		spi_master_transmit(high);
		spi_master_transmit(low);
	 }
	 asm("NOP");
	 MBI_LE_H;
	 asm("NOP");
	 MBI_LE_L;
	 MBI_OE_L;
 }
 #if 0
 void mbi_out(u16 tmp_gui,s8 cnt)
 {
	u8 high,low;
	MBI_LE_L;
//	MBI_OE_H;
	delay_us();
	for (s8 i=0; i<cnt; i++)
	{
		//low = (u8)(tmp_gui+i);
	//	high = (u8)((tmp_gui+i)>>8);
		low = 0xFF;
		high = 0x00;
		//spi_master_transmit(high);
		//spi_master_transmit(low);

		for(s8 j=0; j<16; j++)
		{
			
		}
	}
	MBI_LE_H;
	//delay_us();
	//MBI_LE_L;
	//delay_us();
	MBI_OE_L;
 }
 #endif