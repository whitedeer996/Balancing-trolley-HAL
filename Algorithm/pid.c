#include "pid.h"

PID pid;//�ٶȱջ�PID
PID pid1;//�ٶȻ�PID
PID pid2;//ֱ����PID

void PID_Init()
{
//    pid.kp = 1.1;
//    pid.ki = 0.7;
//    pid.kd = 0.2;
//    pid.kp = 1.5;
//    pid.ki = 2.5;
//    pid.kd = 0.2; //����

	  pid.kp = 1;
    pid.ki = 0;
    pid.kd = 0;
    pid.limit = 1000;
    pid.ek = 0;
    pid.ek_1 = 0;
    pid.ek_2 = 0;//�������ٶȱջ�
	
	  pid1.kp = 0.2;
    pid1.ki = 6;
    pid1.kd = 0;
    pid1.limit = 1000;
    pid1.ek = 0;
    pid1.ek_1 = 0;
    pid1.ek_2 = 0;	
		
	  pid2.kp = 50;//200
//    pid2.ki = 0;//
    pid2.kd = 0.5;//kd����Ϊ��
    pid2.limit = 1000;
    pid2.ek = 0;
    pid2.ek_1 = 0;
    pid2.ek_2 = 0;//ֱ����
}

float PID_Increase(int Encoder,int Target,PID pid)
{
    float pwm = 0;
    pid.ek = Target - Encoder; // ���㵱ǰ���
    pwm = pid.kp*(pid.ek - pid.ek_1)+ pid.ki*pid.ek + pid.kd*(pid.ek - 2*pid.ek_1 + pid.ek_2);   //����ʽpid������
    pid.ek_2 = pid.ek_1; //��������һ�ε�ƫ��
	  pid.ek_1 = pid.ek;   //������һ��ƫ��    
    if(pwm > pid.limit)
    {
      pwm =  pid.limit;
    }
    else if(pwm < -pid.limit)
    {
      pwm =  -pid.limit;
    }
    return pwm;
}//pid.kd*(pid.ek - 2*pid.ek_1 + pid.ek_2)

/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

/**************************************************************************
�������ܣ�λ��ʽpid������
��ڲ���������������λ����Ϣ��Ŀ��λ��
����  ֵ�����PWM
����λ��ʽ��ɢpid��ʽ 
pwm=Kp*e(k)+Ki*��e(k)+Kd[e��k��-e(k-1)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  
��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;����kΪ1,2,,k;
pwm�������
**************************************************************************/
float Position_KP=50,Position_KI=0,Position_KD=0;
int Position_PID (float Angle ,float Gyrox)
{ 	
   float Bias;
   int balance;
   Bias=Angle-0;//����ֱ��ƫ��
   balance=Position_KP*Bias+Gyrox*Position_KD;//����ֱ��PWM
   return balance;//����ֱ��PWM
}

/*�������ٶȻ�*/
int velocity(int encoder_left,int encoder_right)
{
		static float Velocity,Encoder_Least,Encoder;
		static float Encoder_Interal;
		Encoder_Least = (encoder_left+encoder_right)-0;
		Encoder *= 0.7;// 0.7Encoder
		Encoder +=Encoder_Least*0.3;//  "Encoder"=0.7Encoder+Encoder_Least *0.3
		Encoder_Interal += Encoder;
		if(Encoder_Interal>10000)
		{
			Encoder_Interal=10000;
		}
		if(Encoder_Interal<-10000)
		{
			Encoder_Interal=-10000;
		}	
		Velocity = Encoder*pid1.kp+Encoder_Interal*pid1.ki;
		return Velocity;
}



/*������ƽ�⻷*/
int Balance(float Yangle,float GyroxD)
{
		float Bias;
		int balance;
		Bias = Yangle - (0);
		balance =pid2.kp*Bias +pid2.kd*GyroxD;
		return balance;
}
