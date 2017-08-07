#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h"
#include "ov7670.h"
//#include "ov7670cfg.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 


u8 ov_sta;	//帧中断标记
 //外部中断5~9服务程序
void EXTI9_5_IRQHandler(void)
{		 		
	if(EXTI_GetITStatus(EXTI_Line5)==SET)	//是8线的中断
	{   
		if(ov_sta == 1)
		{
			OV7670_WRST=0;	//复位写指针		  		 
			//OV7670_WRST=1;	
			OV7670_WREN=0;	//允许写入FIFO 	
			ov_sta++;		//帧中断加1 			
		}
		else if(!ov_sta)
		{
			OV7670_WRST=0;	//复位写指针		  		 
			OV7670_WRST=1;	
			OV7670_WREN=1;	//允许写入FIFO 	 
			ov_sta++;		//帧中断加1 
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line5);  //清除EXTI8线路挂起位						  
} 
//外部中断9初始化
void EXTI6_Init(void)
{												  
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource5);//PE6 连接到中断线2
	
	 EXTI_InitStructure.EXTI_Line = EXTI_Line5;//LINE6
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE6
	 EXTI_Init(&EXTI_InitStructure);//配置
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断0
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级0
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//子优先级2
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	  NVIC_Init(&NVIC_InitStructure);//配置
	
}









