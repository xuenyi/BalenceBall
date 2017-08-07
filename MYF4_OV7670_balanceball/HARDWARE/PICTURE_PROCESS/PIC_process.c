#include "PIC_process.h"


//u8 image[LENGTH][HEIGHT];
u8 blackline[HEIGHT][3];
u8 whiteline = 0;
u16 linebotton = 0;
void picture_filter(void)
{
		u8 ll,hh;
		for(hh=0;hh<HEIGHT-2;hh++)
			for(ll=0;ll<LENGTH-2;ll++)
			{
				if((image[ll][hh]==1)&&(image[ll+1][hh]==0)&&(image[ll+2][hh]==1))
					image[ll+1][hh]=1;
				else if((image[ll][hh]==0)&&(image[ll+1][hh]==1)&&(image[ll+2][hh]==0))
					image[ll+1][hh]=0;
				
				if((image[ll][hh]==1)&&(image[ll][hh+1]==0)&&(image[ll][hh+2]==1))
					image[ll][hh+1]=1;
				else if((image[ll][hh]==0)&&(image[ll][hh+1]==1)&&(image[ll][hh+2]==0))
					image[ll][hh+1]=0;
			}
			for(ll=0;ll<15;ll++)
				for(hh=0;hh<HEIGHT;hh++)	
				{	
					image[ll][hh]=0;
				}
				
			for(ll=LENGTH-15;ll<LENGTH;ll++)
				for(hh=0;hh<HEIGHT;hh++)	
				{	
					image[ll][hh]=0;
				}
}

void get_blackline(void)
{
	u8 ll,hh,scan_flag = 0,buf1 = 0,buf2 = 0;
	
	whiteline = 0;
	
		for(hh=0;hh<HEIGHT;hh++)
		{
			blackline[hh][0]=0;
			blackline[hh][1]=0;
			for(ll=0;ll<LENGTH;ll++)
			{
				if(image[ll][hh] == 1 && scan_flag == 0) 
				{
					buf1 = ll;
					scan_flag++;
				}
				else if(image[ll][hh] == 0 && scan_flag == 1) 
				{
					buf2 = ll;
					scan_flag++;
				}
				else if(ll == (LENGTH-1) && scan_flag == 1) 
				{
					buf2 = ll;
					scan_flag++;
				
				}
				
				
				if(scan_flag == 2)
				{
					if((blackline[hh][1]-blackline[hh][0]) < (buf2 - buf1))
					{
						blackline[hh][0]=buf1;
						blackline[hh][1]=buf2;
					}
					scan_flag = 0;
				}
			}
			if((blackline[hh][1] - blackline[hh][0])<4)
				whiteline++;
			
			
		}
		
		
}

void blackline_filter(void)
{
	int hh;
	u8 start_flag = 0,i;
	u16 line[8];
	
	
	for(hh=0;hh<HEIGHT-7;hh++)
	{
		
		for(i=0;i<8;i++)
		{
			line[i] = blackline[hh+i][1]-blackline[hh+i][0];
			
		}
		
		for(i=1;i<7;i++)
		{
			if(line[0]>line[i] && line[7]>line[i])
			{
					blackline[hh+i][1] =  (blackline[hh][1] + blackline[hh+7][1])/2;
					blackline[hh+i][0] =  (blackline[hh][0] + blackline[hh+7][0])/2;
			}
		}
	}
	
	for(i=0;i<10;i++)
		{
			if((blackline[i][1]-blackline[i][0]) > (LENGTH - 80))linebotton++;
		}
		
	
	if(!linebotton)
	{
		for(hh=0;hh<HEIGHT-1;hh++)
		{
			if((blackline[hh][1]>(LENGTH-40) || blackline[hh][0]<40 || (blackline[hh][1]-blackline[hh][0])>50 || (blackline[hh][1]-blackline[hh][0])<10 )&& !start_flag) continue;
			else start_flag = 1;
			
			
			if((blackline[hh+1][1]<=blackline[hh][0] || blackline[hh+1][0] >= blackline[hh][1]))
			{
				blackline[hh+1][1] = blackline[hh][1];
				blackline[hh+1][0] = blackline[hh][0];
			}
			if((blackline[hh+1][1]-blackline[hh+1][0])>(blackline[hh][1]-blackline[hh][0]))
			{
				if(blackline[hh+1][1] >= blackline[hh][1] && blackline[hh+1][0] <= blackline[hh][0])
				{
					blackline[hh+1][1] = blackline[hh][1];
					blackline[hh+1][0] = blackline[hh][0];
				}
				else if(blackline[hh+1][1] < blackline[hh][1] && blackline[hh+1][0] <= blackline[hh][0])
				{
					blackline[hh+1][0] = blackline[hh+1][1] - (blackline[hh][1]-blackline[hh][0]);
				}
				else if(blackline[hh+1][1] >= blackline[hh][1] && blackline[hh+1][0] > blackline[hh][0])
				{
					blackline[hh+1][1] = blackline[hh+1][0] + (blackline[hh][1]-blackline[hh][0]);
				}
			}
		}
	}
	else
	{
		for(hh=HEIGHT-1;hh>=0;hh--)
		{

			
			if((blackline[hh-1][1]<=blackline[hh][0] || blackline[hh-1][0] >= blackline[hh][1]))
			{
				blackline[hh-1][1] = blackline[hh][1];
				blackline[hh-1][0] = blackline[hh][0];
			}
			if((blackline[hh-1][1]-blackline[hh-1][0])>(blackline[hh][1]-blackline[hh][0]))
			{
				if(blackline[hh-1][1] >= blackline[hh][1] && blackline[hh-1][0] <= blackline[hh][0])
				{
					blackline[hh-1][1] = blackline[hh][1];
					blackline[hh-1][0] = blackline[hh][0];
				}
				else if(blackline[hh-1][1] < blackline[hh][1] && blackline[hh-1][0] <= blackline[hh][0])
				{
					blackline[hh-1][0] = blackline[hh-1][1] - (blackline[hh][1]-blackline[hh][0]);
				}
				else if(blackline[hh-1][1] >= blackline[hh][1] && blackline[hh-1][0] > blackline[hh][0])
				{
					blackline[hh-1][1] = blackline[hh-1][0] + (blackline[hh][1]-blackline[hh][0]);
				}
			}
		}
	
	
	}
	linebotton = 0;
}
u16 my_abs(int canshu)
{
	return (canshu<0?-canshu:canshu);
}

void get_blackmid(void)
{
	int hh;
	for(hh=0;hh<HEIGHT;hh++)
	{
		blackline[hh][2] = (blackline[hh][0] + blackline[hh][1])/2;	
	}
}

void blackmid_continue(void)
{
	int hh;
	for(hh=0;hh<HEIGHT-3;hh++)
	{
		if(my_abs(blackline[hh+3][2]-blackline[hh][2]) > 20 && my_abs(blackline[hh+3][2]-blackline[hh][2]) < 40)	
		{
			blackline[hh+1][2] = blackline[hh][2];
		}
	}


}

