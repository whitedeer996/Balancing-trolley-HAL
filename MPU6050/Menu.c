#include "STM32OledKey.h"
#include "Menu.h"
#include "pid.h"
#include "motor.h"
#include "math.h"



extern float pitch,roll,yaw; 		  //ŷ����
extern short gyrox,gyroy,gyroz;		//������ԭʼ����

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
	}//��ʾroll
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
	}//��ʾgyrox
	
  OLED_Showdecimal(40,0,roll_OLED,3,2,15);
  OLED_Showdecimal(40,1,gyrox_OLED,3,2,15);
  OLED_Showdecimal(25,2,pid2.kp,3,2,12);
  OLED_Showdecimal(25,3,pid2.kd,3,2,12);
  OLED_Showdecimal(25,5,pid.kp,2,3,12);
  OLED_Showdecimal(25,6,pid.ki,2,3,12);	
}

//0.96��OLED���ΰ�
//K1 K2 K3 K4 K5 �� �� �� �� ����
// |  |  |  |  |  |  |  |  |  |
//77 6F 67 5F 57 76 66 56 5E 6E 

//1.30��OLED���ΰ�
// 1  2  3  4  5  6  7  8  9  *  0  #
// |  |  |  |  |  |  |  |  |  |	 | 
//77 76 75 6F 6E 6D 67 66 65 5F 5E 5D 
void DispPic(unsigned char cKeyNum)//��ʾ�����ƶ���ͼ��
{


	#if(OLEDSIZE==0)//0.96��OLED����10���������������򰴼���
	{
	
		//0.96��OLED���ΰ�
		//K1 K2 K3 K4 K5 �� �� �� �� ����
		// |  |  |  |  |  |  |  |  |  |
		//77 6F 67 5F 57 76 66 56 5E 6E 
		if(cKeyNum==0x6E)//���򰴼����м䰴��
		{
	
		}
		else
		{				
			switch (cKeyNum)
			{//����4���ж�Ϊ�ı�����ֵ
				case 0x76://��
				{
			    Motor_Stop();
					pid2.ek = 0;
          pid2.ek_1 = 0;
          pid2.ek_2 = 0;////�ٶȱջ�PID��ʼ��
					break;
				}
				case 0x56://��
		    	Motor_En();
					break;
				case 0x66://��
           pid2.kp+=10;
					break;
				case 0x5E://��
			     pid2.kp-=5;
			  	break;
				
				//����Ϊ�ı���״
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
	#else//1.30��OLED���ΰ壬��12������
	{
		//1.30��OLED���ΰ�
		// 1  2  3  4  5  6  7  8  9  *  0  #
		// |  |  |  |  |  |  |  |  |  |	 | 
		//77 76 75 6F 6E 6D 67 66 65 5F 5E 5D 
		if(cKeyNum==0x6E)//���򰴼����м䰴��
		{
			(bPicFlag1==0)? (bPicFlag1=1):(bPicFlag1=0);
			if(bPicFlag1==0)
				OLED_ShowCHinese (113,0,11);
			else
				OLED_ShowCHinese (113,0,11+8);				
		}
		else
		{		
			OLED_ShowCHinese (cLocationX,cLocationY,20); 	//�����ϴ���ʾ��ͼ��	
		
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
			if(cLocationX>=128)cLocationX=0;//��������
			if(cLocationY<2)cLocationY=5;
			else if(cLocationY>5)cLocationY=2;
			
			if(bPicFlag2==0)
				OLED_ShowCHinese (cLocationX,cLocationY,cPicIndex); 	//��ʾͼ��	
			else
				OLED_ShowCHinese (cLocationX,cLocationY,cPicIndex+8); 	//��ʾͼ��					
		}			
		
		
	#endif
}


