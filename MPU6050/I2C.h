#ifndef __I2C_H__
#define __I2C_H__

#include "main.h"

/*******************************IIC相关IO口操作**************************************/
//IO口方向
#define IIC_SDA_IN()  {OledData_GPIO_Port->CRH&=0XFFFFFF0F;OledData_GPIO_Port->CRH|=(unsigned int)8<<4;}		//设置SDA输入
#define IIC_SDA_OUT() {OledData_GPIO_Port->CRH&=0XFFFFFF0F;OledData_GPIO_Port->CRH|=(unsigned int)3<<4;}		//设置SDA输出

//IO口操作
#define IIC_SCL(n)    (n?HAL_GPIO_WritePin(OledClk_GPIO_Port,OledClk_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(OledClk_GPIO_Port,OledClk_Pin,GPIO_PIN_RESET)) //SCL
#define IIC_SDA(n)    (n?HAL_GPIO_WritePin(OledData_GPIO_Port,OledData_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(OledData_GPIO_Port,OledData_Pin,GPIO_PIN_RESET))//SDA	 
#define READ_SDA 			 HAL_GPIO_ReadPin(OledData_GPIO_Port,OledData_Pin) //SDA输入

/*****************************IIC函数***************************************/
void oledIIC_Start(void); //启动信号
void oledIIC_Stop(void); //停止信号
void oledIIC_Send_Byte(unsigned char txd); //发送一个字节
unsigned char oledIIC_Read_Byte(unsigned char ack); //读取一个字节
unsigned char oledIIC_Wait_Ack(void);	//等待应答
void oledIIC_Ack(void);	//产生应答
void oledIIC_NAck(void);	//不产生应答
void delay_us(__IO unsigned int delay);

#endif

