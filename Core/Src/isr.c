#include "isr.h"
#include "main.h"
#include "tim.h"
#include "pid.h"
#include "motor.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

extern float pitch,roll,yaw; 		  //欧拉角
extern short gyrox,gyroy,gyroz;		//陀螺仪原始数据

unsigned char RxFlag = 0;      //接收完成标志：0表示接收未完成，1表示接收完成
unsigned char OledKeyFlag = 0; //有按键按下

uint8_t Motor_Flag10ms = 0;
uint8_t Encoder_Flag10ms = 0;
uint8_t MPU6050_10ms_step1 = 0;
uint8_t MPU6050_10ms_step2 = 0;
uint8_t MPU6050_10ms_step3 = 0;
uint8_t MotorPID_Flag50ms = 0;
uint16_t left_encoder_pulse_number= 0;
uint16_t right_encoder_pulse_number = 0;
uint16_t  left_encoder_v= 0;
uint16_t  right_encoder_v = 0;
float Blance_Pwm=0;
float Velocity_Pwm=0;



float Target_Speed=11;//max = 95



uint16_t flag;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
//	static float PWMA=0,PWMB=0;
		
	if(htim->Instance == TIM7)
	{
		Motor_Flag10ms++;
		Encoder_Flag10ms++;
		MPU6050_10ms_step1++;
		if(MPU6050_10ms_step1 == 100)
		{
				MPU6050_10ms_step1 = 0;
				MPU6050_10ms_step2++;
		}
		if(MPU6050_10ms_step2 == 50)
		{
				MPU6050_10ms_step2 = 0;
				
		}
		
		
		
		if(Motor_Flag10ms ==10)//10ms
	  {
				Motor_Flag10ms=0;		
				
			
//				if(roll<=0)
//				{LMotor_TF();RMotor_TF();}
//				else
//				{LMotor_TB();RMotor_TB();}				
        Blance_Pwm=Balance(roll,gyrox);
//				__HAL_TIM_SetCompare(&htim3 ,TIM_CHANNEL_1 ,Blance_Pwm );	
//				__HAL_TIM_SetCompare(&htim3 ,TIM_CHANNEL_2 ,Blance_Pwm );		

//				if(roll>-50&&roll <50)
//				{
//						if(Blance_Pwm<0)
//						{
//							LMotor_TF();
//							RMotor_TF();
//							if(Blance_Pwm <= -7199) Blance_Pwm = -7199;
//							__HAL_TIM_SetCompare(&htim3 ,TIM_CHANNEL_1 ,Blance_Pwm );	
//							__HAL_TIM_SetCompare(&htim3 ,TIM_CHANNEL_2 ,Blance_Pwm );
//						}
//						else if(Blance_Pwm>0)
//						{
//							LMotor_TB();
//							RMotor_TB();
//							if(Blance_Pwm >= 7199) Blance_Pwm = 7199;
//							__HAL_TIM_SetCompare(&htim3 ,TIM_CHANNEL_1 ,Blance_Pwm );	
//							__HAL_TIM_SetCompare(&htim3 ,TIM_CHANNEL_2 ,Blance_Pwm );
//						}
//				}
//				else 
//				{
//					__HAL_TIM_SetCompare(&htim3 ,TIM_CHANNEL_1 ,0 );	
//					__HAL_TIM_SetCompare(&htim3 ,TIM_CHANNEL_2 ,0 );
//				}

		
		}			

		
		if(Encoder_Flag10ms == 10)//10ms
		{
			Encoder_Flag10ms=0;		
			
			left_encoder_v=left_encoder_pulse_number;
			right_encoder_v=right_encoder_pulse_number;
//			printf("%d,%d \r\n",left_encoder_v,right_encoder_v);
			left_encoder_pulse_number=0;
			right_encoder_pulse_number=0;
				
//			PWMA+=PID_Increase(left_encoder_v ,Target_Speed,pid);
//			if(PWMA >7199) PWMA =7199;
//			PWMB+=PID_Increase(right_encoder_v ,Target_Speed,pid);
//			if(PWMB >7199) PWMB =7199;			
//			__HAL_TIM_SetCompare (&htim3 ,TIM_CHANNEL_1 ,(uint32_t)PWMA);	
//			__HAL_TIM_SetCompare (&htim3 ,TIM_CHANNEL_2 ,(uint32_t)PWMB);						
		}

	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_7)
  {
		left_encoder_pulse_number++;
  }
	if (GPIO_Pin == GPIO_PIN_6)
  {
		right_encoder_pulse_number++;
  }
  
	if(GPIO_Pin == OledINT_Pin)
	{
			OledKeyFlag = 1;
  		HAL_GPIO_TogglePin(TestLed_GPIO_Port,TestLed_Pin); 		
	}

}
