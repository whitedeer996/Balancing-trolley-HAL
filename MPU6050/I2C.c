#include "I2C.h"
//���IIC�Ļ�������
/******************************IIC����****************************************/
/*****HAL��΢�뼶��ʱ����*******/
#define CPU_FREQUENCY_MHZ    72		// STM32ʱ����Ƶ   72MHz
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


//I2C��ʼ�ź�
void oledIIC_Start(void)
{
	IIC_SDA_OUT();//SDA����Ϊ���
	IIC_SDA(1);	  	  
	IIC_SCL(1);
	delay_us(4);
 	IIC_SDA(0);//START:when CLK is 1,DATA change form 1 to 0 
	delay_us(4);
	IIC_SCL(0);
}

//I2Cֹͣ�ź�
void oledIIC_Stop(void)
{
	IIC_SDA_OUT();//SDA����Ϊ���
	IIC_SCL(1);
	IIC_SDA(0);//STOP:when CLK is 1 DATA change form 0 to 1
	delay_us(4);
	 
	IIC_SDA(1);		
	delay_us(4);	
}

//�ȴ�Ӧ���źŵ���
//����ֵ�� 1������Ӧ��ʧ��
// 0������Ӧ��ɹ�
unsigned char oledIIC_Wait_Ack(void)
{
//	unsigned char ucErrTime=0;
	IIC_SDA_IN();//SDA����Ϊ����
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
//���� ACK Ӧ��
void oledIIC_Ack(void)
{
	IIC_SCL(0);
	IIC_SDA_OUT();//SDA���	
	IIC_SDA(0);
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
}
//������ ACK Ӧ��
void oledIIC_NAck(void)
{
	IIC_SDA_OUT();//SDA���	
	IIC_SCL(0);
	IIC_SDA(1);
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
	delay_us(2);
}

//IIC ����һ���ֽ�
//����ֵΪ  �ӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void oledIIC_Send_Byte(unsigned char txd)
{
	unsigned char t;
	IIC_SDA_OUT();//SDA���											
	IIC_SCL(0);					//SCL���Ϳ�ʼ���ݴ���
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

//I2C��1���ֽ�,ack=1ʱ,���� ACK,ack=0,����NACK
unsigned char oledIIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	IIC_SDA_IN();														//SDA����Ϊ����
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
		oledIIC_NAck();													//����nACK
	else
		oledIIC_Ack();													//����ACK
	
	return receive;
}



