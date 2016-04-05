/************************************************************************/
/* 名称：AT24C系列驱动
 * 描述：一次写入周期最大5ms,适用于<=AT24C16的型号
 * 编写：邹应龙
 * 修改：2015-07-27
 * 缘由：						*/
/************************************************************************/
#include "config.h"

#define SDA_H		GPIO_SetBits(GPIOC,GPIO_Pin_15);
#define SDA_L		GPIO_ResetBits(GPIOC,GPIO_Pin_15);
#define SCL_H		GPIO_SetBits(GPIOC,GPIO_Pin_14);
#define SCL_L		GPIO_ResetBits(GPIOC,GPIO_Pin_14);

#define SDA_OUT		GPIOC->MODER |= ((uint32_t)1<<30); GPIOC->MODER &=(~((uint32_t)1<<31))			//01输出,00输入
#define SDA_IN		GPIOC->MODER &=(~((uint32_t)1<<30));GPIOC->MODER &=(~((uint32_t)1<<31))			//[30:31]为pin15口设置
#define SDA_READ	GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)
/************************************************************************/
/* 功能：I2C启动
 * 描述：SCL为高时,SDA从高到低
 * 形参：
 * 返回：                 */
/************************************************************************/
static void i2c_start(void)
{
	SDA_OUT;
	SCL_H;
	SDA_H;
	delay_us(4);		//1.8V最小4.7us,3.3V4us足够了
	SDA_L;
	delay_us(4);
	SCL_L;
}
/************************************************************************/
/* 功能：I2C停止
 * 描述：SCL为高时,SDA从低到高
 * 形参：
 * 返回：                 */
/************************************************************************/
static void i2c_stop(void)
{
	SDA_OUT;
	SCL_L;
	SDA_L;
	delay_us(4);
	SCL_H;
	delay_us(4);
	SDA_H;
	delay_us(4);
}

/************************************************************************/
/* 功能：等待回应信号
 * 描述：
 * 形参：
 * 返回：  1应答失败,0成功               */
/************************************************************************/
int32_t i2c_w_ack(void)
{
	int32_t err_time=0;
	SDA_IN;
	SDA_H;
	delay_us(1);
	SCL_H;
	delay_us(1);
	while(SDA_READ)
	{
		err_time++;
		if(err_time > 250)
		{
			i2c_stop();
			return 1;
		}
	}
	SCL_L;
	return 0;
}

/************************************************************************/
/* 功能：产生回应信号
 * 描述：在SCL为低时拉低SDA
 * 形参：
 * 返回：           */
/************************************************************************/
void i2c_ack(void)
{
	SCL_L;
	SDA_OUT;
	SDA_L;
	delay_us(2);
	SCL_H;
	delay_us(2);
	SCL_L;
}
/************************************************************************/
/* 功能：不产生回应信号
 * 描述：在SCL为低时不拉低SDA
 * 形参：
 * 返回：           */
/************************************************************************/
void i2c_nack(void)
{
	SCL_L;
	SDA_OUT;
	SDA_H;
	delay_us(2);
	SCL_H;
	delay_us(2);
	SCL_L;
}

/************************************************************************/
/* 功能：I2C发送一个字节
 * 描述：
 * 形参：
 * 返回：           */
/************************************************************************/
void i2c_s_byte(uint8_t txd)
{
	uint8_t i;
	SDA_OUT;
	SCL_L;		//拉低时数据传输
	for(i=0; i<8; i++)
	{
		if((txd&0x80)>>7)		//高位先发,除了最高位都清零,然后将最高位右移到最低位,再判断
		{
			SDA_H;
		}
		else
		{
			SDA_L;
		}
		delay_us(2);
		txd<<=1;		
		SCL_H;
		delay_us(2);
		SCL_L;
		delay_us(2);
	}
}

/************************************************************************/
/* 功能：I2C读一个字节
 * 描述：
 * 形参：ack=1,发送ack;ack=0,发送nack
 * 返回：           */
/************************************************************************/
uint8_t i2c_r_byte(int32_t ack)
{
	int32_t i,recv;
	SDA_IN;			//输入等待信号
	for(i=0; i<8; i++)
	{
		SCL_L;
		delay_us(2);
		SCL_H;
		recv <<=1;
		if(SDA_READ)
			recv++;
		delay_us(1);
	}
	
	if(!ack)
		i2c_nack();
	else
		i2c_ack();
		
	return recv;
}

/************************************************************************/
/* 功能：at从指定地址读一个数据
 * 描述：写地址->读命令->等待读
 * 形参：地址
 * 返回：           */
/************************************************************************/
uint8_t at24c_r_byte(uint16_t addr)
{
	int32_t tmp=0;
	
	//数据格式=器件地址0xA0+最多三位内存地址+写命令0  ++  8位低内存地址 == 共2字节
	i2c_start();		  	    																 
	i2c_s_byte(0XA0+((addr/256)<<1));   //发送器件地址0XA0+超过8位的地址[最多3位]+写命令(0)	 
	i2c_w_ack();; 
    i2c_s_byte(addr%256);   //发送低地址
	i2c_w_ack();
	
	i2c_start();  	 	   
	i2c_s_byte(0XA1);           //发送读命令			   
	i2c_w_ack();	 
    tmp = i2c_r_byte(0);		//等待读	   
    i2c_stop();//产生一个停止条件
	
	return tmp;
}
/************************************************************************/
/* 功能：at从指定地址写一个数据
 * 描述：
 * 形参：地址
 * 返回：           */
/************************************************************************/
void at24c_w_byte(uint16_t addr,uint8_t data)
{				   	  	    																 
    i2c_start();  
	i2c_s_byte(0XA0+((addr/256)<<1));   //发送器件地址0XA0,写数据 	 
	i2c_w_ack();	   
    i2c_s_byte(addr%256);   //发送低地址
	i2c_w_ack();	 										  		   
	i2c_s_byte(data);     //发送字节							   
	i2c_w_ack();  		    	   
    i2c_stop();//产生一个停止条件 
	delay_ms(10);	 //等待写完成
}

/************************************************************************/
/* 功能：at从指定地址写半字或字的数据
 * 描述：用于写入16bit或32bit数据
 * 形参：地址,数据数组首地址,数据长度2,4
 * 返回：           */
/************************************************************************/
void at24c_w_word(uint16_t addr,uint32_t data)
{  	
	U32_INT tdata;
	tdata.ibuf = data;
	at24c_w_byte(addr,tdata.cbuf[0]);
	at24c_w_byte(addr+1,tdata.cbuf[1]);
	at24c_w_byte(addr+2,tdata.cbuf[2]);
	at24c_w_byte(addr+3,tdata.cbuf[3]);
}
void at24c_w_half(uint16_t addr,uint16_t data)
{
	U16_INT tdata;
	tdata.ibuf = (uint16_t)data;
	at24c_w_byte(addr,tdata.cbuf[0]);
	at24c_w_byte(addr+1,tdata.cbuf[1]);
}
/************************************************************************/
/* 功能：at从指定地址读半字或字的数据
 * 描述：用于读入16bit或32bit数据
 * 形参：地址,数据长度2,4
 * 返回：数据(16bit或32bit)           */
/************************************************************************/
uint32_t at24c_r_word(uint16_t addr)
{  		
	U32_INT tmp;
	tmp.cbuf[0] = at24c_r_byte(addr);
	tmp.cbuf[1] = at24c_r_byte(addr+1);
	tmp.cbuf[2] = at24c_r_byte(addr+2);
	tmp.cbuf[3] = at24c_r_byte(addr+3);
	
	return tmp.ibuf;
}
uint16_t at24c_r_half(uint16_t addr)
{
	U16_INT tmp;
	tmp.cbuf[0] = at24c_r_byte(addr);
	tmp.cbuf[1] = at24c_r_byte(addr+1);
	return tmp.ibuf;
}
/************************************************************************/
/* 功能：at从指定地址n个数组的数据
 * 描述：
 * 形参：地址,数组首地址,数据个数
 * 返回：           */
/************************************************************************/
void at24c_w_queue(uint16_t addr,uint8_t *arr,uint16_t num)
{
	while(num--)
	{
		at24c_w_byte(addr,*arr);
		addr++;
		arr++;
	}
}
/************************************************************************/
/* 功能：at从指定地址读n个数组数据
 * 描述：
 * 形参：地址,用于存放数据的数组地址,数据个数
 * 返回：           */
/************************************************************************/
void at24c_r_queue(uint16_t addr,uint8_t *arr,uint16_t num)
{
	while(num)
	{
		*arr++=at24c_r_byte(addr++);	
		num--;
	}
}

/************************************************************************/
/* 功能：检测AT24Cxx是否正常,再最后一个地址写数据来判断
 * 描述：C01=127,C02=255,C04=511,C08=1023,C16=2047
 * 形参：
 * 返回：正常返回0,失败返回1           */
/************************************************************************/
uint8_t at24c_check(void)
{
	uint32_t tmp;
	tmp=at24c_r_word(2036);
	if(tmp==0x234d7c9a) return 0;
	else
	{
		at24c_w_word(2036,0x234d7c9a);
		tmp = at24c_r_word(2036);
		if(tmp==0x234d7c9a)return 0;
	}
	return 1;
}
  


