/************************************************************************/
/* 名称：AT24C01 02 04等相关驱动
 * 描述：
 * 编写：邹应龙
 * 修改：2015-07-28
 * 缘由：						*/
/************************************************************************/
#ifndef _AT24C_H
#define _AT24C_H

void at24c_w_byte(uint16_t addr,uint8_t data);
uint8_t at24c_r_byte(uint16_t addr);

void at24c_w_word(uint16_t addr,uint32_t data);
uint32_t at24c_r_word(uint16_t addr);

void at24c_w_half(uint16_t addr,uint16_t data);
uint16_t at24c_r_half(uint16_t addr);

void at24c_w_queue(uint16_t addr,uint8_t *arr,uint16_t num);
void at24c_r_queue(uint16_t addr,uint8_t *arr,uint16_t num);

uint8_t at24c_check(void);
#endif
