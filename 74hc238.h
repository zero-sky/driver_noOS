#ifndef _74HC238_H
#define _74HC238_H


//输出使能
#define HC238_EN_H		PORTB |=1<<0
#define HC238_EN_L		PORTB &=~(1<<0)

//A0输入
#define HC238_A0_H		PORTC |=1<<5
#define HC238_A0_L		PORTC &=~(1<<5)

#define HC238_A1_H		PORTB |=1<<2
#define HC238_A1_L		PORTB &=~(1<<2)

#define HC238_A2_H		PORTB |=1<<1
#define HC238_A2_L		PORTB &=~(1<<1)

void hc238_enable(void);
void hc238_disable(void);
void hc238_out(u8 output);

#endif