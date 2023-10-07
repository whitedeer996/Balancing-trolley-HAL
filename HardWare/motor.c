#include "motor.h"
#include "isr.h"
#include "pid.h"

void MotorInit(void)
{  
   Motor_En();
	 LMotor_TF(); 
	 RMotor_TF();
}

/*TB6612ʹ��*/
void Motor_En(void)
{
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);	
}

/*TB6612ʧ��*/
void Motor_Stop(void)
{
   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
}

/*������ת*/
void LMotor_TF(void)
{
   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_SET);
}

/*������ת*/
void LMotor_TB(void)
{
   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_RESET);
}

/*�ҵ����ת*/
void RMotor_TF(void)
{
   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_SET);
}

/*�ҵ����ת*/
void RMotor_TB(void)
{
   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_RESET);
}



