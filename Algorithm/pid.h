#ifndef __PID_H__
#define __PID_H__


typedef struct PID
{ 
  float kp;
  float ki;
  float kd;
  float ek;     //��ǰ���
  float ek_1;   //��һ�����
  float ek_2;   //����һ�����
  float limit;  //�޷�
}PID;

void PID_Init(void);
float PID_Increase(int Encoder,int Target,PID pid);
int Position_PID(float Angle ,float Gyrox);
int Balance(float Yangle,float GyroxD);

extern PID pid;//�ٶȱջ�PID
extern PID pid1;//�ٶȻ�PID
extern PID pid2;//ֱ����PID
extern float Position_KP;
extern float Position_KI;
extern float Position_KD;//λ�û�PID
#endif 
