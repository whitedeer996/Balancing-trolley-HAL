#ifndef __STM32OLEDKEY_H__
#define __STM32OLEDKEY_H__

#include "OLED_Font.h"
#include "stm32f1xx_hal.h"

#define OLEDSIZE 0 //0-为0.96寸OLED调参板，1为1.30寸OLED调参板
#define OLEDTYPE1106 0//0-OLED为SH1106主控，0-OLED为SSD1306主控，

/***********************************
模块引脚
	VCC:3.3V
	SDA:PB9
	SCL:PB8
	INT:PB15
	GND:GND
说明：
	1.按键按下，触发中断，通过IIC发送回按键值，不同按键对应不同键值
	2.中断引脚自带上拉电阻，当扫描到按键按下，变为低电平，故接到外部中断，下降沿触发
	3.自带硬件消抖，直接读取键值判断即可
	4.OLED屏与按键共用iic接口，但互不干扰
	5.CH455芯片设置系统参数中的亮度和七段、八段模式指的是数码管，模块没有接，与OLED无关
	6.OLED屏一会亮一会暗可能是硬件问题，不常见
********************************CH455芯片设置*************************************/
// 设置系统参数命令
#define CH455_BIT_ENABLE	0x01		// 开启/关闭位
#define CH455_BIT_SLEEP		0x04		// 睡眠控制位
#define CH455_BIT_7SEG		0x08		// 7段控制位
#define CH455_BIT_INTENS1	0x10		// 1级亮度
#define CH455_BIT_INTENS2	0x20		// 2级亮度
#define CH455_BIT_INTENS3	0x30		// 3级亮度
#define CH455_BIT_INTENS4	0x40		// 4级亮度
#define CH455_BIT_INTENS5	0x50		// 5级亮度
#define CH455_BIT_INTENS6	0x60		// 6级亮度
#define CH455_BIT_INTENS7	0x70		// 7级亮度
#define CH455_BIT_INTENS8	0x00		// 8级亮度

#define CH455_SYSOFF	0x00		// 关闭显示、关闭键盘
#define CH455_SYSON		CH455_BIT_ENABLE 	// 开启显示、键盘
#define CH455_SLEEPOFF	CH455_SYSOFF	// 关闭睡眠
#define CH455_SLEEPON	( CH455_SYSOFF | CH455_BIT_SLEEP )	// 开启睡眠
#define CH455_7SEG_ON	( CH455_SYSON | CH455_BIT_7SEG )	// 开启七段模式
#define CH455_8SEG_ON	( CH455_SYSON | 0x00 )	// 开启八段模式
#define CH455_SYSON_4	( CH455_SYSON | CH455_BIT_INTENS4 )	// 开启显示、键盘、4级亮度
#define CH455_SYSON_8	( CH455_SYSON | CH455_BIT_INTENS8 )	// 开启显示、键盘、8级亮度

// 加载字数据命令
#define CH455_DIG0		0x68			// 数码管位0显示,需另加8位数据
#define CH455_DIG1		0x6A			// 数码管位1显示,需另加8位数据
#define CH455_DIG2		0x6C			// 数码管位2显示,需另加8位数据
#define CH455_DIG3		0x6E			// 数码管位3显示,需另加8位数据

// 读（按键）操作字节1
#define CH455_GET_KEY	0x4F					// 读取按键值

//写操作字节1
#define CH455_WriteCmd 0x48      //写入命令

// CH455接口定义（已经或运算到读写命令字节1中）
#define		CH455_I2C_ADDR		0x40			// CH455的地址
#define		CH455_I2C_MASK		0x3E			// CH455的高字节命令掩码

/*****************************OLED屏参数设置******************************************/
//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness 0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	 

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


/*****************************CH455函数**************************************/
void OledKeyInit(void); //OLED、CH455初始化函数
void CH455_Write(unsigned char cmd);  //CH455写命令
unsigned char CH455_ReadKeyCode(void);  //CH455读取按键值


/*按键值（若不同屏按键值不一样，可能硬件电路不同，校准即可）
按键1--> 119  按键2--> 118  按键3--> 117
按键4--> 111  按键5--> 110  按键6--> 109
按键7--> 103  按键8--> 102  按键9--> 101
按键*--> 95   按键0--> 94   按键#--> 93 
*/

/****************************OLED控制函数**********************************/
void OLED_Init(void);
void OLED_IIC_Write_Command(unsigned char IIC_Command);
void OLED_IIC_Write_Data(unsigned char IIC_Data);
void OLED_WR_Byte(unsigned char dat,unsigned char cmd);
void fill_picture(unsigned char fill_Data);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_Display_On(void);//打开显示
void OLED_Display_Off(void);//关闭显示
void OLED_Clear(void);//清屏函数
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char size);//显示字符
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned long num,unsigned char len,unsigned char size);//显示数字
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr,unsigned char size);//显示字符串
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no);  //显示中文
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]); //显示图片
unsigned long oled_pow(unsigned char m,unsigned char n); 
void OLED_Showdecimal(unsigned char x,unsigned char y,float num,unsigned char z_len,unsigned char f_len,unsigned char size2);//显示小数
void OLED_DrawPoint(unsigned char x,unsigned char y,unsigned char t);//画点
void OledKeyBeep( unsigned int time);
	

#endif

