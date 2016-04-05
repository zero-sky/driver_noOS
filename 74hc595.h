#ifndef _74HC595_H_
#define _74HC595_H_

//串行输入口
#define GRID_DS_H		PORTA |=1<<1
#define GRID_DS_L		PORTA &=~(1<<1)
#define LED_DS_H		PORTD |=1<<3
#define LED_DS_L		PORTD &=~(1<<3)

//移位寄存器时钟
#define SH_CP_H		PORTD |=1<<5
#define SH_CP_L		PORTD &=~(1<<5)

//数据输出使能
#define ST_CP_H		PORTD |=1<<4
#define ST_CP_L		PORTD &=~(1<<4)

void hc595_out(u8 *led_data,u8 *grid_data);
#endif