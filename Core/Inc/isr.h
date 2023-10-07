#ifndef __ISR_H__
#define __ISR_H__

#include "main.h"
extern unsigned char RxFlag;
extern unsigned char OledKeyFlag;
extern uint8_t Motor_Flag10ms;
extern uint8_t MotorPID_Flag50ms;
extern uint16_t left_encoder_pulse_number;
extern uint16_t right_encoder_pulse_number;
extern float Blance_Pwm;
extern float Velocity_Pwm;
#endif 
