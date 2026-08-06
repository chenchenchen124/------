#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "oled.h"
#include "dht11.h"
#include "IIC.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"
#include "misc.h"
#include "TIM.h"
#include "AD.h"
#include "LED.h"
#include "usart.h"

extern int flag,result_lx;
int number;
u16 temp,humi,MQ2,water,ir;
void task(void);

int main(void)
{
	delay_init();
	LED_Init();
	OLED_Init();
	AD_Init();
	USART1_Init(9600);
	Timer2_Init(4999,7199);
	DHT11_Init2();
	OLED_ShowString(1, 1,"TIME:");
	OLED_ShowString(3, 1,"temp:");
	OLED_ShowString(3, 10,"humi:");
	OLED_ShowString(4, 1,"water:         %");
	while(1)
	{	

		OLED_ShowNum(1,8,number,6);
		OLED_ShowNum(3,6,temp,2);
        OLED_ShowNum(3,15,humi,2);
		OLED_ShowNum(4,8,water,6);
		task();
//		delay_ms(100);
	}
	
}

void task(void)
{
	if(water>=70)
	{BEEN_ON();}
	else BEEN_OFF();


}

void TIM2_IRQHandler(void)   //TIM3�ж� 
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM3�жϷ������:TIM3 �ж�Դ 
	{
		number++;
		if(AD_GetValue(ADC_Channel_1)<=200)
		{
			water=0;
		}
		if(AD_GetValue(ADC_Channel_1)>=1300)
		{
			water=100;
		}
		else water=((AD_GetValue(ADC_Channel_1)-0)/13);
//		water=AD_GetValue(ADC_Channel_1);
		DHT11_Read_Data2(&temp,&humi);
	}
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIM3���жϴ�����λ:TIM3 �ж�Դ 
}



