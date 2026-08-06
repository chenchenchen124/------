#ifndef __IIC_H
#define __IIC_H 

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"
#include "misc.h"

#define I2CSLAVE_ADDR           0x36 << 1  // 地址 0x36
#define I2C1_CLOCK_FRQ          100000     // 通信速度 (100 kHz)
#define I2C1_RAM_SIZE           256        // 数组大小
#define I2C1_MODE_WAITING       0          // 等待命令
#define I2C1_MODE_SLAVE_ADR_WR  1          // 写标志
#define I2C1_MODE_ADR_BYTE      2          // 收到的字节
#define I2C1_MODE_DATA_BYTE_WR  3          // 写数据字节
#define I2C1_MODE_SLAVE_ADR_RD  4          // 读标志
#define I2C1_MODE_DATA_BYTE_RD  5          

void I2C1_Ram_Init(void);
void I2C1_ClearFlag(void);
void Set_I2C1_Ram(uint8_t adr, uint8_t val);
void I2C1_Slave_Init(void);
uint8_t Get_I2C1_Ram(uint8_t adr);


#endif