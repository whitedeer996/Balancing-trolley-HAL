#include "I2C.h"
#include "STM32OledKey.h"


/*********************OLED、按键CH455、蜂鸣器初始化函数*********************************/
void OledKeyInit(void)
{
	OLED_Init(); //初始化OLED
	OLED_Clear();	 //OLED清屏
	OledKeyBeep(500);	//检验蜂鸣器
	CH455_Write(CH455_SYSON_8);//按键模块初始化
//CH455初始化函数，向芯片写入一个启动信号即可
}

/****************蜂鸣器函数********************/
/*
   （1）DIG0_DIG3直接接GND
   （2）给四个位的A段写高电平（即四个数码管对应的A段） A段对应的是SEG0，芯片的9脚
   （3）函数需传入形参时间，单位为ms
   （4）因为动态扫描，所以要开将四位的A段全部置一才可以实现占空比近似为1，此时蜂鸣器才可正常响
   （5）蜂鸣器与按键不可同时使用，在蜂鸣器响完结束后要在关蜂鸣器函数重新对CH455初始化
*/
void OledKeyBeep( unsigned int time)
{
   oledIIC_Start();                //启动信号
	 oledIIC_Send_Byte(CH455_DIG3);  //写字节1,寻到要写的地址，DIG3--DIG0的地址是6E,6C,6A,68
	 oledIIC_Ack();                  //产生应答信号
   oledIIC_Send_Byte(0x01);        //写字节2,   0000 0001，点亮A段，蜂鸣器响
	 oledIIC_Ack(); 
	 oledIIC_Stop();
	
	 oledIIC_Start();                //启动信号
	 oledIIC_Send_Byte(CH455_DIG2);  //写字节1
	 oledIIC_Ack();                  //产生应答信号
   oledIIC_Send_Byte(0x01);       //写字节2
	 oledIIC_Ack(); 
	 oledIIC_Stop();
	
	 oledIIC_Start();                //启动信号
	 oledIIC_Send_Byte(CH455_DIG1);  //写字节1
	 oledIIC_Ack();                 //产生应答信号
   oledIIC_Send_Byte(0x01);        //写字节2
	 oledIIC_Ack(); 
	 oledIIC_Stop();
	
	 oledIIC_Start();                   //启动信号
	 oledIIC_Send_Byte(CH455_DIG0);  //写字节1
	 oledIIC_Ack();                   //产生应答信号
   oledIIC_Send_Byte(0x01);         //写字节2
	 oledIIC_Ack(); 
	 oledIIC_Stop();	
	
	 HAL_Delay (time);

///关蜂鸣器函数/
//   在蜂鸣器响完后要加上CH455_Write(CH455_SYSON_8);重新对CH455芯片初始化

	 oledIIC_Start();//启动信号
	 oledIIC_Send_Byte(CH455_DIG3);  //写字节1
	 oledIIC_Ack();  //产生应答信号
   oledIIC_Send_Byte(0x00);//写字节2
	 oledIIC_Ack(); 
	 oledIIC_Stop();
	
	 oledIIC_Start();//启动信号
	 oledIIC_Send_Byte(CH455_DIG2);  //写字节1
	 oledIIC_Ack();  //产生应答信号
   oledIIC_Send_Byte(0x00);//写字节2
	 oledIIC_Ack(); 
	 oledIIC_Stop();
	
	 oledIIC_Start();//启动信号
	 oledIIC_Send_Byte(CH455_DIG1);  //写字节1
	 oledIIC_Ack();  //产生应答信号
   oledIIC_Send_Byte(0x00);//写字节2
	 oledIIC_Ack(); 
	 oledIIC_Stop();
	
	 oledIIC_Start();//启动信号
	 oledIIC_Send_Byte(CH455_DIG0);  //写字节1
	 oledIIC_Ack();  //产生应答信号
   oledIIC_Send_Byte(0x00);//写字节2
	 oledIIC_Ack(); 
	oledIIC_Stop();	
   CH455_Write(CH455_SYSON_8);
}
/***************************
CH455写操作函数
输入参数cmd：具体的命令字节
函数执行过程：1.产生启动信号
							2.发送“写命令”字节，即01001000B，即48H
							3.产生应答1
							4.发送具体命令（1个字节）
							5.产生应答2
							6.产生停止信号
***************************/
void CH455_Write(unsigned char cmd)
{
	oledIIC_Start();//启动信号
	oledIIC_Send_Byte(CH455_WriteCmd);  //写命令发送字节1
	oledIIC_Ack();  //产生应答信号
	oledIIC_Send_Byte(cmd);  //写入命令
	oledIIC_Ack();  //产生应答信号
	oledIIC_Stop(); //停止信号
}

/***************************
CH455读操作函数（读按键代码）
函数执行过程：1.产生启动信号
							2.发送“读命令”字节1，即 01001111B，即4FH
							3.产生应答1
							4.读取字节2（具体按键代码）
							5.产生应答2
							6.产生停止信号
***************************/
unsigned char CH455_ReadKeyCode(void)
{
	unsigned char KeyCode;
	oledIIC_Start();//启动信号
	oledIIC_Send_Byte(CH455_GET_KEY);  //读按键发送字节1
	oledIIC_Ack();  //产生应答信号
	KeyCode=oledIIC_Read_Byte(1); //读取字节2，产生应答信号
	oledIIC_Stop(); //停止信号
	
	return KeyCode;
}


/****************************OLED函数*****************************************/
//OLED写命令
void OLED_IIC_Write_Command(unsigned char IIC_Command)
{

	oledIIC_Start();
  oledIIC_Send_Byte(0x78);            //Slave address,SA0=0
	oledIIC_Wait_Ack();	
  oledIIC_Send_Byte(0x00);			//write command
	oledIIC_Wait_Ack();	
  oledIIC_Send_Byte(IIC_Command); 
	oledIIC_Wait_Ack();	
  oledIIC_Stop();
}
//OLED写数据
void OLED_IIC_Write_Data(unsigned char IIC_Data)
{
	oledIIC_Start();
  oledIIC_Send_Byte(0x78);			//D/C#=0; R/W#=0
	oledIIC_Wait_Ack();	
  oledIIC_Send_Byte(0x40);			//write data
	oledIIC_Wait_Ack();	
  oledIIC_Send_Byte(IIC_Data);
	oledIIC_Wait_Ack();	
  oledIIC_Stop();
}
//OLED写字符（字符是数据或者命令）
void OLED_WR_Byte(unsigned char data,unsigned char cmd)
{
	if(cmd)
	{
   OLED_IIC_Write_Data(data);
	}
	else
	{
	 OLED_IIC_Write_Command(data);
	}
}

void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}

//坐标设置
	void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	#if(!OLEDTYPE1106)//SSDC1306
	{	
		OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
		OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
	}
	#else//SH1106
	{	
		OLED_WR_Byte((((x+2)&0xf0)>>4)|0x10,OLED_CMD);
		OLED_WR_Byte(((x+2)&0x0f)|0x01,OLED_CMD); 
	}
	#endif
		
}   	  
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	unsigned char i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		#if(!OLEDTYPE1106)//SSDC1306
		OLED_WR_Byte (0x02,OLED_CMD);      //设置显示位置—列低地址
		#else//SH1106
		OLED_WR_Byte (0x02,OLED_CMD);      //设置显示位置—列低地址
		#endif
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(size ==16)
		{
		if(x>Max_Column-1){x=0;y=y+2;}
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
		OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
		}
		else {	
		if(x>Max_Column-1){x=0;y=y+1;}
			OLED_Set_Pos(x,y);
			for(i=0;i<6;i++)
			OLED_WR_Byte(F6x8[c][i],OLED_DATA);
			
		}
}
//m^n函数
unsigned long oled_pow(unsigned char m,unsigned char n)
{
	unsigned long result=1;	 
	while(n--)result*=m;    
	return result;
}				  


//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned long num,unsigned char len,unsigned char size)
{         	
	unsigned char t,temp;
	unsigned char enshow=0;	
	if(size==16)            //F8*16
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ',size);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',size); 
	}
	else                   //F6*12
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+6*t,y,' ',size);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+6*t,y,temp+'0',size); 
	}

} 
/**
  * @brief   显示一个字符号串
  * @param   x : uint8_t 起点列坐标 
  * @param   y : uint8_t 起点行坐标 
  * @param   chr : uint8_t *字符串指针
  * @param   size : 16：16*16字符，其他：6*8字符
  * @retval  无
  */
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr,unsigned char size)
{
	unsigned char j=0;
	if(size==16)
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
	else 
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],size);
			x+=6;
		if(x>120){x=0;y+=1;}
			j++;
	}
}
//显示汉字
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no)
{      			    
	unsigned char t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}

/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 

//显示小数
//z_len为整数显示位数，f_len为小数显示位数，size2为字体大小
void OLED_Showdecimal(unsigned char x,unsigned char y,float num,unsigned char z_len,unsigned char f_len,unsigned char size2)
{         	
	unsigned char t,temp;
	unsigned char enshow;
	int z_temp,f_temp;      
	z_temp=(int)num;
	//整数部分
	for(t=0;t<z_len;t++)
	{
		temp=(z_temp/oled_pow(10,z_len-t-1))%10;
		if(enshow==0 && t<(z_len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}
			else
			enshow=1;
		}
		OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
	//小数点
	OLED_ShowChar(x+(size2/2)*(z_len),y,'.',size2); 
	
	f_temp=(int)((num-z_temp)*(oled_pow(10,f_len)));
  //小数部分
	for(t=0;t<f_len;t++)
	{
		temp=(f_temp/oled_pow(10,f_len-t-1))%10;
		OLED_ShowChar(x+(size2/2)*(t+z_len)+5,y,temp+'0',size2); 
	}
}

//画点 
//x:0~127
//y:0~63
//t:1 填充 0,清空	
void OLED_DrawPoint(unsigned char x,unsigned char y,unsigned char t)
{
	OLED_Set_Pos(x,y);
	OLED_WR_Byte(t,OLED_DATA);
	
}

//OLED初始化函数
void OLED_Init(void)
{
//	OLED_IIC_Init();
	HAL_Delay(100);
//RESET THE OLED
 	#if 0
  OLED_RST_Set();
	delay_ms(100);
	OLED_RST_Clr();
	delay_ms(100);
	OLED_RST_Set();
	#endif
					  
  OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	#if(!OLEDTYPE1106)//SSDC1306
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	#else//SH1106
	OLED_WR_Byte(0x00+2,OLED_CMD);//---set low column address
	#endif
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128   
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 	

}
