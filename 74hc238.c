/************************************************************************/
/* 功能：按键HC238键盘驱动
 * 描述：PB0/1/2 数据 PA0 使能
 * 形参：1<<n,n表示是第几位拉高
 * 返回：                            */
/************************************************************************/
#include "../main.h"

inline
void hc238_enable(void)
{
   	HC238_EN_H;
}
inline
void hc238_disable(void)
{
	HC238_EN_L;
}
void hc238_out(u8 output)
{
	switch(output)
	{
		case 0x01:HC238_A0_L;HC238_A1_L;HC238_A2_L;break;						//000
		case 0x02:HC238_A0_H;HC238_A1_L;HC238_A2_L;break;		//001
		case 0x04:HC238_A0_L;HC238_A1_H;HC238_A2_L;break;		//010
		case 0x08:HC238_A0_H;HC238_A1_H;HC238_A2_L;break;		//011
		case 0x10:HC238_A0_L;HC238_A1_L;HC238_A2_H;break;		//100
		case 0x20:HC238_A0_H;HC238_A1_L;HC238_A2_H;break;		//101
		case 0x40:HC238_A0_L;HC238_A1_H;HC238_A2_H;break;		//110
		case 0x80:HC238_A0_H;HC238_A1_H;HC238_A2_H;break;						//111
		default:break;
	}
}