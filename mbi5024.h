/************************************************************************/
/* 名称：MBI5020/5024/5026等16位恒流芯片驱动
 * 描述：
 * 编写：邹应龙
 * 修改：2016-11-26
 * 缘由：*/
/************************************************************************/
#ifndef MBI5024_H_
#define MBI5024_H_

#define MBI_LE_H	PORTD |=1<<4
#define MBI_LE_L	PORTD &=~(1<<4)
#define MBI_OE_H	PORTD |=1<<5
#define MBI_OE_L	PORTD &=~(1<<5)

#define MBI_SDI_H	PORTB |=1<<5
#define MBI_SDI_L	PORTB &=~(1<<5)
#define MBI_CLK_H	PORTB |=1<<7
#define MBI_CLK_L	PORTB &=~(1<<7)

void mbi_out(u16 *buf,s8 cnt);


#endif /* MBI5024_H_ */