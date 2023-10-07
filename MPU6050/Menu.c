#include "STM32OledKey.h"
#include "Menu.h"
#include "pid.h"
#include "motor.h"
#include "math.h"



extern float pitch,roll,yaw; 		  //欧拉角
extern short gyrox,gyroy,gyroz;		//陀螺仪原始数据

float roll_OLED;
short gyrox_OLED;

void MainMenu(void)
{
  OLED_ShowString(0,0,"roll:",8);
  OLED_ShowString(0,1,"gyrx:",8);
  OLED_ShowString(0,2,"kp2:",8);
  OLED_ShowString(0,3,"kd2:",8);
  OLED_ShowString(0,5,"kp:",8);
  OLED_ShowString(0,6,"ki:",8);		
}


void Oled_Displaying()
{
	if(roll >= 0)
	{
		roll_OLED = roll;
		OLED_ShowString(30,0,"+",8);
	}
	else
	{
		roll_OLED = roll;
		roll_OLED = fabs(roll_OLED);
		OLED_ShowString(30,0,"-",8);	
	}//显示roll
	if(gyrox >= 0)
	{
		gyrox_OLED = gyrox;
		OLED_ShowString(30,1,"+",8);
	}
	else
	{
		gyrox_OLED = gyrox;
		gyrox_OLED = fabs(gyrox_OLED);
		OLED_ShowString(30,1,"-",8);	
	}//显示gyrox
	
  OLED_Showdecimal(40,0,roll_OLED,3,2,15);
  OLED_Showdecimal(40,1,gyrox_OLED,3,2,15);
  OLED_Showdecimal(25,2,pid2.kp,3,2,12);
  OLED_Showdecimal(25,3,pid2.kd,3,2,12);
  OLED_Showdecimal(25,5,pid.kp,2,3,12);
  OLED_Showdecimal(25,6,pid.ki,2,3,12);	
}

//0.96寸OLED调参板
//K1 K2 K3 K4 K5 左 上 右 下 按下
// |  |  |  |  |  |  |  |  |  |
//77 6F 67 5F 57 76 66 56 5E 6E 

//1.30寸OLED调参板
// 1  2  3  4  5  6  7  8  9  *  0  #
// |  |  |  |  |  |  |  |  |  |	 | 
//77 76 75 6F 6E 6D 67 66 65 5F 5E 5D 
void DispPic(unsigned char cKeyNum)//显示可以移动的图形
{


	#if(OLEDSIZE==0)//0.96寸OLED，有10个按键（包括五向按键）
	{
	
		//0.96寸OLED调参板
		//K1 K2 K3 K4 K5 左 上 右 下 按下
		// |  |  |  |  |  |  |  |  |  |
		//77 6F 67 5F 57 76 66 56 5E 6E 
		if(cKeyNum==0x6E)//五向按键，中间按下
		{
	
		}
		else
		{				
			switch (cKeyNum)
			{//以下4个判断为改变坐标值
				case 0x76://左
				{
			    Motor_Stop();
					pid2.ek = 0;
          pid2.ek_1 = 0;
          pid2.ek_2 = 0;////速度闭环PID初始化
					break;
				}
				case 0x56://右
		    	Motor_En();
					break;
				case 0x66://上
           pid2.kp+=10;
					break;
				case 0x5E://下
			     pid2.kp-=5;
			  	break;
				
				//以下为改变形状
				case 0x77://K1

					break;
				case 0x6F://K2
	
					break;
				case 0x67://K3								
					break;			
				case 0x5F://K4
	
					break;
				case 0x57://K5

					break;				
				default:;
			}	//switch

			
	
		}	
	}
	#else//1.30寸OLED调参板，有12个按键
	{
		//1.30寸OLED调参板
		// 1  2  3  4  5  6  7  8  9  *  0  #
		// |  |  |  |  |  |  |  |  |  |	 | 
		//77 76 75 6F 6E 6D 67 66 65 5F 5E 5D 
		if(cKeyNum==0x6E)//五向按键，中间按下
		{
			(bPicFlag1==0)? (bPicFlag1=1):(bPicFlag1=0);
			if(bPicFlag1==0)
				OLED_ShowCHinese (113,0,11);
			else
				OLED_ShowCHinese (113,0,11+8);				
		}
		else
		{		
			OLED_ShowCHinese (cLocationX,cLocationY,20); 	//擦除上次显示的图形	
		
			switch (cKeyNum)
			{
				case 0x6F://4
					if(cLocationX==0)cLocationX=128;
					cLocationX = cLocationX-4;
					break;
				case 0x6D://6
					cLocationX = cLocationX+4;
					break;
				case 0x76://2
					cLocationY = cLocationY - 1;
					break;
				case 0x66://8
					cLocationY = cLocationY + 1;
					break;
				case 0x77://1
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=4;
					break;
				case 0x75://3
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=5;			
					break;
				case 0x67://7
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=6;			
					break;			
				case 0x65://9
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=7;			
					break;
				case 0x5F://*
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=8;			
					break;	
				case 0x5E://0
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=9;			
					break;	
				case 0x5D://#
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
//					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=10;			
					break;					
				default:;
			}	
		}
			if(cLocationX>=128)cLocationX=0;//调整坐标
			if(cLocationY<2)cLocationY=5;
			else if(cLocationY>5)cLocationY=2;
			
			if(bPicFlag2==0)
				OLED_ShowCHinese (cLocationX,cLocationY,cPicIndex); 	//显示图形	
			else
				OLED_ShowCHinese (cLocationX,cLocationY,cPicIndex+8); 	//显示图形					
		}			
		
		
	#endif
}


