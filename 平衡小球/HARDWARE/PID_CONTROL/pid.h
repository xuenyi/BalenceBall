#ifndef __PID_H
#define __PID_H	
#include "sys.h" 
#include "delay.h"

typedef struct
{
float Ek_now,EK_last,Integral,Kp,Ki,Kd,P_out,I_out,D_out,PID_out;
}PID_Date;

extern PID_Date Weiyi,Angle;

void PID_calculate(PID_Date Select_pid,float aim,float measure,float *outval);
void Pid_set(PID_Date *Select_pid,float kp,float ki,float kd);

#endif 


