/************************************************************************/
/* 名称：TM1640驱动
 * 简介：LED和LCD是不同的
 * 简介：舒华5918
 * 编写：邹应龙
 * 更新：2015-1-24
 * 缘由：在输入数据时当CLK是高电平时，DIN上的信号必须保持不变     */
/************************************************************************/

#include "config.h"

static uint8_t light_led[8] = {0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F};
/************************************************************************/
/* 功能：指针函数
 * 描述：选择哪一个芯片使能
 * 形参：
 * 返回：
 * 修改：                             */
/************************************************************************/
void (*tm1640_clk_h)(void);
void (*tm1640_clk_l)(void);
void (*tm1640_din_h)(void);
void (*tm1640_din_l)(void);

static void u4_clk_h(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_11);
	delay_us(2);
}
static void u4_clk_l(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_11);
	delay_us(2);
}
static void u4_din_h(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_12);
	delay_us(2);
}
static void u4_din_l(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
	delay_us(2);
}
void u4_enable(void)
{
	tm1640_clk_h = u4_clk_h;
	tm1640_clk_l = u4_clk_l;
	tm1640_din_h = u4_din_h;
	tm1640_din_l = u4_din_l;
}
///////////////////////////////
static void u5_clk_h(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_11);
	delay_us(2);
}
static void u5_clk_l(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_11);
	delay_us(2);
}
static void u5_din_h(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_10);
	delay_us(2);
}
static void u5_din_l(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_10);
	delay_us(2);
}
void u5_enable(void)
{
	tm1640_clk_h = u5_clk_h;
	tm1640_clk_l = u5_clk_l;
	tm1640_din_h = u5_din_h;
	tm1640_din_l = u5_din_l;
}
//////////////////////////////
static void u6_clk_h(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	delay_us(2);
}
static void u6_clk_l(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	delay_us(2);
}
static void u6_din_h(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_9);
	delay_us(2);
}
static void u6_din_l(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_9);
	delay_us(2);
}
void u6_enable(void)
{
	tm1640_clk_h = u6_clk_h;
	tm1640_clk_l = u6_clk_l;
	tm1640_din_h = u6_din_h;
	tm1640_din_l = u6_din_l;
}
//////////////////////////////
static void u7_clk_h(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	delay_us(2);
}
static void u7_clk_l(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	delay_us(2);
}
static void u7_din_h(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_15);
	delay_us(2);
}
static void u7_din_l(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_15);
	delay_us(2);
}
void u7_enable(void)
{
	tm1640_clk_h = u7_clk_h;
	tm1640_clk_l = u7_clk_l;
	tm1640_din_h = u7_din_h;
	tm1640_din_l = u7_din_l;
}
//////////////////////////////
static void u8_clk_h(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	delay_us(2);
}
static void u8_clk_l(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	delay_us(2);
}
static void u8_din_h(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	delay_us(2);
}
static void u8_din_l(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	delay_us(2);
}
void u8_enable(void)
{
	tm1640_clk_h = u8_clk_h;
	tm1640_clk_l = u8_clk_l;
	tm1640_din_h = u8_din_h;
	tm1640_din_l = u8_din_l;
}

//////////////////////////////
static void u9_clk_h(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	delay_us(2);
	
}
static void u9_clk_l(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	delay_us(2);
}
static void u9_din_h(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	delay_us(2);
}
static void u9_din_l(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	delay_us(2);
}
void u9_enable(void)
{
	tm1640_clk_h = u9_clk_h;
	tm1640_clk_l = u9_clk_l;
	tm1640_din_h = u9_din_h;
	tm1640_din_l = u9_din_l;
}
///////////////////////////////
/************************************************************************/
/* 功能：开始传输
 * 描述：CLK为高时，DIN由高变低
 * 形参：
 * 返回：
 * 修改：                             */
/************************************************************************/
static void tm1640_start(void)
{
	(*tm1640_clk_h)();
	(*tm1640_din_h)();
	(*tm1640_din_l)();
	(*tm1640_clk_l)();
}

/************************************************************************/
/* 功能：结束传输
 * 描述：CLK为高时，DIN由低变高
 * 形参：
 * 返回：
 * 修改：                             */
/************************************************************************/
static void tm1640_stop(void)
{
	(*tm1640_clk_l)();
	(*tm1640_din_l)();
	(*tm1640_clk_h)();
	(*tm1640_din_h)();		//最后拉高锁住
}

/************************************************************************/
/* 功能：写入1
 * 描述：
 * 形参：
 * 返回：
 * 修改：                             */
/************************************************************************/
static void tm1640_w_1(void)
{
	(*tm1640_clk_l)();
	(*tm1640_din_h)();
	(*tm1640_clk_h)();
	(*tm1640_clk_l)();
}
/************************************************************************/
/* 功能：写入0
 * 描述：
 * 形参：
 * 返回：
 * 修改：                             */
/************************************************************************/
static void tm1640_w_0(void)
{
	(*tm1640_clk_l)();
	(*tm1640_din_l)();
	(*tm1640_clk_h)();
	(*tm1640_clk_l)();
}
/************************************************************************/
/* 功能：写入8个数据
 * 描述：低位在前，高位在后
 * 形参：
 * 返回：
 * 修改：                             */
/************************************************************************/
void tm1640_w_byte(u8 data)
{
	for (u8 i=0;i<8;i++)
	{
		if (data&0x01)
			tm1640_w_1();
		else
			tm1640_w_0();
		data >>= 1;
	}
}

/************************************************************************/
/* 功能：连续写数据，地址自动加1
 * 描述：开始-设置数据-结束 开始-设置地址-显示数据1-显示数据n-结束 开始-控制显示-结束
 * 形参：led地址，显示数据数目(最多有16个),数据数组第一个元素地址
 * 返回：
 * 修改：                             */
/************************************************************************/
void tm1640_w_quence(uint8_t addr,uint8_t num,uint8_t *data)
{
	tm1640_start();
	tm1640_w_byte(0x40);		//0100 0000地址自动加1
	//tm1640_w_byte(0x44);//固定地址	
	tm1640_stop();

	tm1640_start();
	tm1640_w_byte(0xC0+addr);		//1100 XXXX设置地址数据，第一个地址
	for (s32 i=0; i<num; i++)	        //连续输入数据
	{
		tm1640_w_byte(*(data+i));
	}

	tm1640_stop();

	tm1640_start();
	tm1640_w_byte(light_led[sys.light]);		//调节亮度
	tm1640_stop();
}

/************************************************************************/
/* 功能：固定地址写数据
 * 描述：开始-设置数据-结束 开始-设置地址1-显示数据1-结束 开始-设置数据n-显示数据n-结束 开始-控制显示-结束
 * 形参：地址  数据
 * 返回：
 * 修改：                             */
/************************************************************************/
void tm1640_w_data(uint8_t addr, uint8_t data)
{
	tm1640_start();
	tm1640_w_byte(0x44);		//0100 0100固定地址
	tm1640_stop();

	tm1640_start();
	tm1640_w_byte(addr+0xC0);
	tm1640_w_byte(data);
	tm1640_stop();

	tm1640_start();
	tm1640_w_byte(light_led[sys.light]);		//调节亮度
	tm1640_stop();
}

