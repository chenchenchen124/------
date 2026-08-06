#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_8| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_8| GPIO_Pin_3);
}

void BEEN_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_11);
}

void BEEN_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_11);
}

void BEEN_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11) == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_11);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_11);
	}
}

void LED2_OFF(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
}

void LED2_ON(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_12);
}

void LED2_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12) == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_12);
	}
}

void JDQ_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
}

void JDQ_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
}

void FAN_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
}

void FAN_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
}
