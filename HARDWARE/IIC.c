#include "IIC.h"

uint8_t i2c1_mode = I2C1_MODE_WAITING;
uint8_t i2c1_ram_adr = 0;
uint8_t i2c1_ram[I2C1_RAM_SIZE];//在这个数组里面写入需要发送的数据

uint8_t Get_I2C1_Ram(uint8_t adr) 
{
    return i2c1_ram[adr];
}

void Set_I2C1_Ram(uint8_t adr, uint8_t val) 
{
    i2c1_ram[adr] = val;
    return;
}

void I2C1_Ram_Init(void)//初始化时引用 默认数组为0-255
{
    uint16_t i;
    for (i = 0; i < 256; i++)
    {
        Set_I2C1_Ram(i, i);
    }
}

void I2C1_Slave_Init(void) 
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    I2C_InitTypeDef  I2C_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    /* 配置iic引脚 */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* 配置优先级 */
    NVIC_InitStructure.NVIC_IRQChannel                   = I2C1_EV_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* 将 I2C 错误中断配置为具有更高的优先级 */
    NVIC_InitStructure.NVIC_IRQChannel = I2C1_ER_IRQn;
    NVIC_Init(&NVIC_InitStructure);

    /* 初始化 */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = I2CSLAVE_ADDR;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = I2C1_CLOCK_FRQ;

    /* 使能iic */
    I2C_Cmd(I2C1, ENABLE);

    /* 打开iic */
    I2C_Init(I2C1, &I2C_InitStructure);

    I2C_ITConfig(I2C1, I2C_IT_EVT, ENABLE); 
    I2C_ITConfig(I2C1, I2C_IT_BUF, ENABLE);
    I2C_ITConfig(I2C1, I2C_IT_ERR, ENABLE); 

    I2C1_Ram_Init();
}

void I2C1_ClearFlag(void) 
{
    /* 清除标志位 */
    while((I2C1->SR1 & I2C_SR1_ADDR) == I2C_SR1_ADDR) 
    {
        I2C1->SR1;
        I2C1->SR2;
    }

    /* 清除标志位 */
    while((I2C1->SR1&I2C_SR1_STOPF) == I2C_SR1_STOPF) 
    {
        I2C1->SR1;
        I2C1->CR1 |= 0x1;
    }
}

void I2C1_EV_IRQHandler(void) 
{
    uint8_t wert;
    uint32_t event;

    /* 读取最后一次 event */
    event = I2C_GetLastEvent(I2C1);
    if(event == I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED) 
    {
        // 主机已发送从地址 向从机发送数据
        i2c1_mode = I2C1_MODE_SLAVE_ADR_WR;
    }
    else if(event == I2C_EVENT_SLAVE_BYTE_RECEIVED) 
    {
        // 主机已向从机发送了一个字节
        wert = I2C_ReceiveData(I2C1);
        // 检查地址
        if(i2c1_mode == I2C1_MODE_SLAVE_ADR_WR) 
        {
            i2c1_mode = I2C1_MODE_ADR_BYTE;
            // 设置当前需要发送的数据位置
            i2c1_ram_adr = wert;
        }
        else 
        {
            i2c1_mode = I2C1_MODE_DATA_BYTE_WR;
            // 储存数据
            Set_I2C1_Ram(i2c1_ram_adr, wert);
            // 地址自增
            i2c1_ram_adr++;
        }
    }
    else if(event == I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED) 
    {
        // 主机已发送从机地址 从机读取数据
        i2c1_mode = I2C1_MODE_SLAVE_ADR_RD;
        // 读取数组数据
        wert = Get_I2C1_Ram(i2c1_ram_adr);
        // 将数据发送到主机
        I2C_SendData(I2C1, wert);
        // 地址自增
        i2c1_ram_adr++;
    }
    else if(event == I2C_EVENT_SLAVE_BYTE_TRANSMITTED) 
    {
        // 主机想从从机读取另一个字节的数据
        i2c1_mode = I2C1_MODE_DATA_BYTE_RD;
        // 读取数组数据
        wert = Get_I2C1_Ram(i2c1_ram_adr);
        // 发送到主机
        I2C_SendData(I2C1, wert);
        // 地址自增
        i2c1_ram_adr++;
    }
    else if(event == I2C_EVENT_SLAVE_STOP_DETECTED) 
    {
        I2C1_ClearFlag();
        i2c1_mode = I2C1_MODE_WAITING;
    }
}

void I2C1_ER_IRQHandler(void) 
{
    if (I2C_GetITStatus(I2C1, I2C_IT_AF)) 
    {
        I2C_ClearITPendingBit(I2C1, I2C_IT_AF);
    }
}
