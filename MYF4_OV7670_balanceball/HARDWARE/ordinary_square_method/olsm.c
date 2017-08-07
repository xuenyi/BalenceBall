#include "olsm.h"
#include "PIC_process.h"


void ordinary_lsm(float *kk,float *dd)
{
	float Ex = 0.0f,Ey = 0.0f,Exy = 0.0f,Ex2 = 0.0f,my_k = 0.0f,my_d = 0.0f;
	int num = 0;
	for(num = 0;num<HEIGHT;num++)
	{
		Ex += (float)num;
		Ey += (float)blackline[num][2];
		Exy += (float)num * (float)blackline[num][2];
		Ex2 += (float)num * (float)num;
	}
	
	my_k = (num*Exy-Ex*Ey)/(num*Ex2-Ex*Ex);
	my_d = (Ey-my_k*Ex)/(float)num;
	
	*kk = my_k;
	*dd = my_d;
	
}







