/************************************************************************/
/* ���ƣ�TD����,��595��������
 * ������
 * ��д����Ӧ��
 * �޸ģ�2015-07-04
 * Ե�ɣ��滪5517*/
/************************************************************************/
#include "../main.h"


/************************************************************************/
/* ���ܣ�
 * ����������ǰ��������ȴ��룬�±������ݺ���
 * �βΣ�
 * ���أ���    */
/************************************************************************/
void hc595_out(u8 *data, s8 n)
{
	s8 i,j,byte;
  	SH_CP_L;
  	ST_CP_L;
  	for(i=0; i<n; i++)
  	{
		byte = data[i];
	  	for(j=0; j<8; j++)
	  	{
		  	if(byte&0x80)		DS_H;			//��������Ǹ�λ
		  	else 				DS_L;
		  	byte<<=1;
		  		
		  	SH_CP_H;
		  	SH_CP_L;
	  	}
  	}
  	ST_CP_H;			//���	
}

void td62783_clear(void)
{
	u8 data[2] = {0,0};
	hc595_out(data,2);
}
void td62783_out(u16 td)
{
	u8 data[2];
	data[1] = (u8)td;
	data[0] = (u8)(td>>8);
	hc595_out(data,2);
}