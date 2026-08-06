#ifndef _USART_H_
#define _USART_H_


#include "stm32f10x.h"
#include "LED.h"

void USART1_Init(unsigned int baud);
void USART2_Init(unsigned int baud);
void USART3_Init(unsigned int baud);
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);

#endif 
