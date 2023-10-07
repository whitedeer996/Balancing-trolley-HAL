#include "pid.h"

PID pid;//速度闭环PID
PID pid1;//速度环PID
PID pid2;//直立环PID

void PID_Init()
{
//    pid.kp = 1.1;
//    pid.ki = 0.7;
//    pid.kd = 0.2;
//    pid.kp = 1.5;
//    pid.ki = 2.5;
//    pid.kd = 0.2; //三轮

	  pid.kp = 1;
    pid.ki = 0;
    pid.kd = 0;
    pid.limit = 1000;
    pid.ek = 0;
    pid.ek_1 = 0;
    pid.ek_2 = 0;//编码器速度闭环
	
	  pid1.kp = 0.2;
    pid1.ki = 6;
    pid1.kd = 0;
    pid1.limit = 1000;
    pid1.ek = 0;
    pid1.ek_1 = 0;
    pid1.ek_2 = 0;	
		
	  pid2.kp = 50;//200
//    pid2.ki = 0;//
    pid2.kd = 0.5;//kd极性为正
    pid2.limit = 1000;
    pid2.ek = 0;
    pid2.ek_1 = 0;
    pid2.ek_2 = 0;//直立环
}

float PID_Increase(int Encoder,int Target,PID pid)
{
    float pwm = 0;
    pid.ek = Target - Encoder; // 计算当前误差
    pwm = pid.kp*(pid.ek - pid.ek_1)+ pid.ki*pid.ek + pid.kd*(pid.ek - 2*pid.ek_1 + pid.ek_2);   //增量式pid控制器
    pid.ek_2 = pid.ek_1; //保存上上一次的偏差
	  pid.ek_1 = pid.ek;   //保存上一次偏差    
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
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

/**************************************************************************
函数功能：位置式pid控制器
入口参数：编码器测量位置信息，目标位置
返回  值：电机PWM
根据位置式离散pid公式 
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
**************************************************************************/
float Position_KP=50,Position_KI=0,Position_KD=0;
int Position_PID (float Angle ,float Gyrox)
{ 	
   float Bias;
   int balance;
   Bias=Angle-0;//计算直立偏差
   balance=Position_KP*Bias+Gyrox*Position_KD;//计算直立PWM
   return balance;//返回直立PWM
}

/*下面是速度环*/
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



/*下面是平衡环*/
int Balance(float Yangle,float GyroxD)
{
		float Bias;
		int balance;
		Bias = Yangle - (0);
		balance =pid2.kp*Bias +pid2.kd*GyroxD;
		return balance;
}
