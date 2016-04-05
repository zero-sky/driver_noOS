/************************************************************************/
/* 名称：tm1640驱动
 * 描述：
 * 编写：邹应龙
 * 修改：2014-12-04
 * 缘由：	*/
/************************************************************************/

#ifndef _TM1640_H
#define _TM1640_H

//#define LED_LIGHT	0x8D		//亮度范围0x88~0x8F
void u4_enable(void);			//led上
void u5_enable(void);			//led中
void u6_enable(void);			//点阵左一
void u7_enable(void);			//点阵左二
void u8_enable(void);			//点阵左三
void u9_enable(void);			//点阵左四
void tm1640_w_quence(uint8_t addr,uint8_t num,uint8_t *data);
void tm1640_w_data(uint8_t addr, uint8_t data);
void tm1640_w_byte(u8 data);
#endif /* LCD_H_ */
