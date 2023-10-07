#ifndef __PID_H__
#define __PID_H__


typedef struct PID
{ 
  float kp;
  float ki;
  float kd;
  float ek;     //当前误差
  float ek_1;   //上一次误差
  float ek_2;   //上上一次误差
  float limit;  //限幅
}PID;

void PID_Init(void);
float PID_Increase(int Encoder,int Target,PID pid);
int Position_PID(float Angle ,float Gyrox);
int Balance(float Yangle,float GyroxD);

extern PID pid;//速度闭环PID
extern PID pid1;//速度环PID
extern PID pid2;//直立环PID
extern float Position_KP;
extern float Position_KI;
extern float Position_KD;//位置环PID
#endif 
