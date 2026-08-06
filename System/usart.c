#include "usart.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>



/*
************************************************************
*	函数名称	USART1_Init
*
*	函数功能	usart1初始化
*
*	入口参数	baud：设定波特率
*
0*	00+	返回参数	无
*
*	说明		TX-PA9		RX-PA10
************************************************************
*/
void USART1_Init(unsigned int baud)
{

	GPIO_InitTypeDef GPIO_initstruct;
	USART_InitTypeDef usart_initstruct;
	NVIC_InitTypeDef nvic_initstruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//PA9	TXD
	GPIO_initstruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_initstruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_initstruct);
	
	//PA10	RXD
	GPIO_initstruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_initstruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_initstruct);
	
	usart_initstruct.USART_BaudRate = baud;
	usart_initstruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件流控制
	usart_initstruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//接受和发送
	usart_initstruct.USART_Parity = USART_Parity_No;									//无效验
	usart_initstruct.USART_StopBits = USART_StopBits_1;								    //1位停止位
	usart_initstruct.USART_WordLength = USART_WordLength_8b;							//8位数据位
	USART_Init(USART1, &usart_initstruct);
	
	USART_Cmd(USART1, ENABLE);														//使能串口
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);									//使能接受中断
	
	nvic_initstruct.NVIC_IRQChannel = USART1_IRQn;
	nvic_initstruct.NVIC_IRQChannelCmd = ENABLE;
	nvic_initstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_initstruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&nvic_initstruct);

}

/*
************************************************************
*	函数名称	Usart2_Init
*
*	函数功能	usart2初始化
*
*	入口参数	baud：设定波特率
*
*	返回参数	无
*
*	说明		TX-PA2		RX-PA3
************************************************************
*/
void USART2_Init(unsigned int baud)
{
	GPIO_InitTypeDef GPIO_initstruct;
	USART_InitTypeDef usart_initstruct;
	NVIC_InitTypeDef nvic_initstruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	//PA2	TXD
	GPIO_initstruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_initstruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_initstruct);
	
	//PA3	RXD
	GPIO_initstruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_initstruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_initstruct);
	
	usart_initstruct.USART_BaudRate = baud;
	usart_initstruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件流控制
	usart_initstruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//接受和发送
	usart_initstruct.USART_Parity = USART_Parity_No;									//无效验
	usart_initstruct.USART_StopBits = USART_StopBits_1;								    //1位停止位
	usart_initstruct.USART_WordLength = USART_WordLength_8b;							//8位数据位
	USART_Init(USART2, &usart_initstruct);
	
	USART_Cmd(USART2, ENABLE);														//使能串口
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);									//使能接受中断
	
	nvic_initstruct.NVIC_IRQChannel = USART2_IRQn;
	nvic_initstruct.NVIC_IRQChannelCmd = ENABLE;
	nvic_initstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_initstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvic_initstruct);
}

/*
************************************************************
*	函数名称	Usart3_Init
*
*	函数功能	usart3初始化
*
*	入口参数	baud：设定波特率
*
*	返回参数	无
*
*	说明		TX-PB10		RX-PB11
************************************************************
*/
void USART3_Init(unsigned int baud)
{
	GPIO_InitTypeDef GPIO_initstruct;
	USART_InitTypeDef usart_initstruct;
	NVIC_InitTypeDef nvic_initstruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	//PB10	TXD
	GPIO_initstruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_initstruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_initstruct);
	
	//PB11	RXD
	GPIO_initstruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_initstruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_initstruct);
	
	usart_initstruct.USART_BaudRate = baud;
	usart_initstruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件流控制
	usart_initstruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//接受和发送
	usart_initstruct.USART_Parity = USART_Parity_No;									//无效验
	usart_initstruct.USART_StopBits = USART_StopBits_1;								    //1位停止位
	usart_initstruct.USART_WordLength = USART_WordLength_8b;							//8位数据位
	USART_Init(USART3, &usart_initstruct);
	
	USART_Cmd(USART3, ENABLE);														//使能串口
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);									//使能接受中断
	
	nvic_initstruct.NVIC_IRQChannel = USART3_IRQn;
	nvic_initstruct.NVIC_IRQChannelCmd = ENABLE;
	nvic_initstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_initstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvic_initstruct);
}

/*
************************************************************
*	函数名称	Usart_SendString
*
*	函数功能	串口数据发送
*
*	入口参数	USART：串口组
*				str：要发送的数据
*				len：数据长度
*
*	返回参数	无
*
*	说明		
************************************************************
*/
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{
	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);									//发送数据
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//等待发送完成
	}

}

/*
************************************************************
*	函数名称	UsartPrintf
*
*	函数功能	格式化打印
*
*	入口参数	USARTx:串口组
*				fmt：不定长参
*
*	返回参数	无
*
*	说明		
************************************************************
*/
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{
	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//格式化
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}
}

int flag;
void USART1_IRQHandler(void)
{
    // 检查是否为接收中断
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        uint8_t received_data = USART_ReceiveData(USART1); // 读取接收到的数据

//        if (received_data == 'A') //投喂
//        {
//            Stepper_RotateByStep(Forward,600, 3); 
//        }
//        if (received_data == 'B')//开风扇
//        {
//            FAN_ON();
//        }
//        if (received_data == 'C') //关风扇
//        {
//            FAN_OFF();
//        }
//        if (received_data == 'D') //自动添水
//        {
//            flag=0;
//        }
//        if (received_data == 'E') //开水泵
//        {
//            flag=1;
//			JDQ_ON();
//        }
//        if (received_data == 'F') //关水泵
//        {
//			flag=1;
//            JDQ_OFF();
//        }
        // 清除中断标志
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}

