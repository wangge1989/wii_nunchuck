/**
 * joystick.c: wii Nunchuck joystick low level driver
 */
#include <stdbool.h>
#include <stdint.h>

#include "stm32f30x.h"

/*FreeRtos includes*/
#include "FreeRTOS.h"
#include "task.h"

/* project includes */
#include "nvicconf.h"
#include "joystick.h"


/* Private variables */
static bool isInit = false;

void i2c_interrupt_handler(void)
{
}

bool joystick_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    I2C_InitTypeDef  I2C_InitStructure;
    //NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable I2C1 peripheral clock */
    RCC_APB2PeriphClockCmd(JOYSTICK_I2C_CLK, ENABLE);
    
    /* Enable SDA, SCL GPIO clock */
    RCC_AHBPeriphClockCmd(JOYSTICK_GPIO_I2C_CLK, ENABLE);

    GPIO_PinAFConfig(JOYSTICK_GPIO_I2C_PORT, JOYSTICK_GPIO_I2C_SDA_SOURCE, JOYSTICK_GPIO_I2C_AF);
    GPIO_PinAFConfig(JOYSTICK_GPIO_I2C_PORT, JOYSTICK_GPIO_I2C_SCL_SOURCE, JOYSTICK_GPIO_I2C_AF);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    /* I2C SDA pin configuration */
    GPIO_InitStructure.GPIO_Pin = JOYSTICK_GPIO_I2C_SDA;
    GPIO_Init(JOYSTICK_GPIO_I2C_PORT, &GPIO_InitStructure);

    /* I2C SCL pin configuration */
    GPIO_InitStructure.GPIO_Pin = JOYSTICK_GPIO_I2C_SCL;
    GPIO_Init(JOYSTICK_GPIO_I2C_PORT, &GPIO_InitStructure);

    /* I2C configuration -------------------------------------------------------*/
    I2C_InitStructure.I2C_Mode                = I2C_Mode_I2C;
    I2C_InitStructure.I2C_AnalogFilter        = I2C_AnalogFilter_Enable;
    I2C_InitStructure.I2C_DigitalFilter       = 0x00;
    I2C_InitStructure.I2C_OwnAddress1         = 0x00;
    I2C_InitStructure.I2C_Ack                 = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_Timing              = 0x00100209;
  
    /* Apply JOYSTICK_I2C configuration before enable it */
    I2C_Init(JOYSTICK_I2C, &I2C_InitStructure);

    /* Enable and set I2C Interrupt to the assigned priority */
    //NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
    //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_JOYSTICK_PRI;
    //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
    //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //NVIC_Init(&NVIC_InitStructure);

    //SPI_I2S_ITConfig(JOYSTICK_SPI, SPI_I2S_IT_RXNE, ENABLE);

    /* JOYSTICK_I2C Peripheral Enable */
    I2C_Cmd(JOYSTICK_I2C, ENABLE);

    isInit = true;

    return isInit;
}

bool joystick_test(void)
{
    return isInit;
}

/***********************
 * I2C private methods *
 ***********************/
uint8_t joystick_write(uint8_t device_addr, uint8_t reg_addr,
                       uint8_t* p_buffer, uint16_t num_byte_to_write)
{
    return 0;
}

uint8_t joystick_read(uint8_t device_addr, uint8_t reg_addr,
                      uint8_t* p_buffer, uint16_t num_byte_to_read)
{
    return 0;
}
