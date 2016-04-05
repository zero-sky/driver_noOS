/************************************************************************/
/* 名称：音频驱动文件
 * 描述：
 * 编写：邹应龙
 * 修改：2014-12-25
 * 缘由：*/
/************************************************************************/
#include "config.h"
#define	SDA_H   GPIO_SetBits(GPIOB, GPIO_Pin_9)
#define SDA_L	GPIO_ResetBits(GPIOB, GPIO_Pin_9)
#define SCK_H	GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define SCK_L	GPIO_ResetBits(GPIOB, GPIO_Pin_8)
//共十一段音频，低10位有效,下标越大声音越小
//0.8.16.24.32.40.48.56.64.72.80		
//static u8 mem_vol[11]={0,8,16,24,32,40,48,56,64,72,80};
static u8 mem_vol[11]={0,4,8,12,16,20,24,32,40,48,56};
static int8_t	cnt_vol=6;
/************************************************************************/
/* 功能：音频初始化
 * 描述：
 * 形参：
 * 返回：                  */
/************************************************************************/
void audio_init(void)
{
	SDA_L;
	SCK_L;
}
/************************************************************************/
/* 功能：声音调节。能调节左/右/双声道
 * 描述：
 * 形参：衰减值[0~83]，左/右声道(0代表左还是右是未定义的)，=0双通道/=1单通道
 * 返回：                  */
/************************************************************************/
static void audio_set_vol (u8 volume, u8 channel, u8 both)
{
	u8 bits;
	u16 data = 0; // control word is built by OR-ing in the bits

	if(volume>83)		//超出上限不响应
		return;
	data |= (channel << 0); 				// D0 (channel select: 0=ch1, 1=ch2)
	data |= (both << 1); 					// D1 (individual/both select: 0=both, 1=individual)
	data |= ((21 - (volume / 4)) << 2); 	// D2...D6 (ATT1: coarse attenuator: 0,-4dB,-8dB, etc.. steps of 4dB)
	data |= ((3 - (volume % 4)) << 7);	 	// D7...D8 (ATT2: fine attenuator: 0...-1dB... steps of 1dB)
	data |= (0x03<< 9); 					// D9...D10  D9 & D10 must both be 1
	flag.debug = data;
	//时钟的上升沿读取数据
	for (bits = 0; bits < 11; bits++) 		// send out 11 control bits
	{ 					
		delay_us (2); // pg.4 - M62429P/FP datasheet
		SDA_L;
		delay_us (2);
		SCK_L;
		delay_us (2);
		if((data >> bits) & 0x01)		SDA_H;
		else							SDA_L;
		delay_us (2);
		SCK_H;
	}
	
	//在时钟的下降沿锁存数据
	delay_us (2);
	SDA_H;// final clock latches data in
	
	delay_us (2);
	SCK_L;
}
/************************************************************************/
/* 功能：声音调节。
 * 描述：三个函数，分别控制左/右/双通道的调节
 * 形参：衰减值。取值范围0~83
 * 返回：                  */
/************************************************************************/
void audio_left (uint8_t volume) // set CH1 (pins 1 [in] and 2 [out])
{
	audio_set_vol (volume, 0, 1);
}

void audio_right (uint8_t volume) // set CH2 (pins 8 [in] and 7 [out])
{
	audio_set_vol (volume, 1, 1);
}

void audio_both(uint8_t volume) // both simultaneously
{
	audio_set_vol (volume, 0, 0);
}
/************************************************************************/
/* 功能：声音调节
 * 描述：
 * 形参：
 * 返回：                  */
/************************************************************************/
void vol_up(void)
{
	if(cnt_vol<10)
	{
		beep_on(BEEP_SHORT,1);
		cnt_vol++;
	}
	else
	{
		beep_on(BEEP_LONG,1);
		cnt_vol = 10;
	}

	audio_both(mem_vol[cnt_vol]);
}
void vol_down(void)
{
	if(cnt_vol>0)
	{
		beep_on(BEEP_SHORT,1);
		cnt_vol--;
	}
	else
	{
		beep_on(BEEP_LONG,1);
		cnt_vol = 0;
	}

	audio_both(mem_vol[cnt_vol]);
}
void vol_comfirm(void)
{
	beep_on(BEEP_SHORT,1);
	if(cnt_vol ==10)	cnt_vol = 5;
	else				cnt_vol = 10;		//下标最大为静音

	audio_both(mem_vol[cnt_vol]);
}
