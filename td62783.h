/************************************************************************/
/* 名称：TD数据,用595传递数据
 * 描述：
 * 编写：邹应龙
 * 修改：2015-07-04
 * 缘由：舒华5517*/
/************************************************************************/


#ifndef TD62783_H_
#define TD62783_H_

#define SH_CP_H		PORTB |=1<<1
#define SH_CP_L		PORTB &=~(1<<1)
#define ST_CP_H		PORTB |=1<<0
#define ST_CP_L		PORTB &=~(1<<0)
#define DS_H		PORTA |=1<<6
#define DS_L		PORTA &=~(1<<6)

void td62783_clear(void);
void td62783_out(u16 td);

#endif /* TD62783_H_ */