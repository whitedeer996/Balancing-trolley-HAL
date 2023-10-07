#include "I2C.h"
//软件IIC的基本函数
/******************************IIC函数****************************************/
/*****HAL库微秒级延时函数*******/
#define CPU_FREQUENCY_MHZ    72		// STM32时钟主频   72MHz
void delay_us(__IO unsigned int delay)
{
    int last, curr, val;
    int temp;
    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = SysTick->VAL;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = SysTick->VAL;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
              val = SysTick->VAL;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;
    }
}


//I2C起始信号
void oledIIC_Start(void)
{
	IIC_SDA_OUT();//SDA设置为输出
	IIC_SDA(1);	  	  
	IIC_SCL(1);
	delay_us(4);
 	IIC_SDA(0);//START:when CLK is 1,DATA change form 1 to 0 
	delay_us(4);
	IIC_SCL(0);
}

//I2C停止信号
void oledIIC_Stop(void)
{
	IIC_SDA_OUT();//SDA设置为输出
	IIC_SCL(1);
	IIC_SDA(0);//STOP:when CLK is 1 DATA change form 0 to 1
	delay_us(4);
	 
	IIC_SDA(1);		
	delay_us(4);	
}

//等待应答信号到来
//返回值： 1，接收应答失败
// 0，接收应答成功
unsigned char oledIIC_Wait_Ack(void)
{
//	unsigned char ucErrTime=0;
	IIC_SDA_IN();//SDA设置为输入
	IIC_SDA(1);//delay_us(1);
	IIC_SCL(1);//delay_us(1);
//	while(READ_SDA)
//	{
//		ucErrTime++;
//		if(ucErrTime>250)
//		{
//			IIC_Stop();
//			return 1;
//		}
//	}
	IIC_SCL(0);	
	return 0;
} 
//产生 ACK 应答
void oledIIC_Ack(void)
{
	IIC_SCL(0);
	IIC_SDA_OUT();//SDA输出	
	IIC_SDA(0);
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
}
//不产生 ACK 应答
void oledIIC_NAck(void)
{
	IIC_SDA_OUT();//SDA输出	
	IIC_SCL(0);
	IIC_SDA(1);
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
	delay_us(2);
}

//IIC 发送一个字节
//返回值为  从机有无应答
//1，有应答
//0，无应答
void oledIIC_Send_Byte(unsigned char txd)
{
	unsigned char t;
	IIC_SDA_OUT();//SDA输出											
	IIC_SCL(0);					//SCL拉低开始数据传输
	for(t = 0; t < 8; t++)
	{
	IIC_SDA((txd & 0x80) >> 7);
	txd <<= 1;
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
	delay_us(2);
	}
}

//I2C读1个字节,ack=1时,发送 ACK,ack=0,发送NACK
unsigned char oledIIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	IIC_SDA_IN();														//SDA设置为输入
	for (i = 0; i < 8; i++)
	{
		IIC_SCL(0);
		delay_us(2);
		IIC_SCL(1);
		delay_us(2);
    receive <<= 1;
    if (READ_SDA) receive++;
	}
	if (!ack)
		oledIIC_NAck();													//发送nACK
	else
		oledIIC_Ack();													//发送ACK
	
	return receive;
}



