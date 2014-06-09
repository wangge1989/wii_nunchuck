/**
 * joystick.c: ps2 joystick low level driver
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

uint8_t spi_send_byte(uint8_t byte);
uint8_t spi_receive_byte(void);

/* Private variables */
static bool isInit = false;

void spi_interrupt_handler(void)
{
}

bool joystick_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
    //NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable the SPI periph */
    RCC_APB2PeriphClockCmd(JOYSTICK_SPI_CLK, ENABLE);
    
    /* Enable CS  GPIO clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

    /* Enable CS, SCK, MOSI and MISO GPIO clocks */
    RCC_AHBPeriphClockCmd(JOYSTICK_GPIO_SPI_CLK, ENABLE);

    GPIO_PinAFConfig(JOYSTICK_GPIO_SPI_PORT, JOYSTICK_GPIO_SPI_CS_SOURCE, JOYSTICK_GPIO_SPI_AF);
    GPIO_PinAFConfig(JOYSTICK_GPIO_SPI_PORT, JOYSTICK_GPIO_SPI_SCK_SOURCE, JOYSTICK_GPIO_SPI_AF);
    GPIO_PinAFConfig(JOYSTICK_GPIO_SPI_PORT, JOYSTICK_GPIO_SPI_MISO_SOURCE, JOYSTICK_GPIO_SPI_AF);
    GPIO_PinAFConfig(JOYSTICK_GPIO_SPI_PORT, JOYSTICK_GPIO_SPI_MOSI_SOURCE, JOYSTICK_GPIO_SPI_AF);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    /* SPI CS pin configuration */
    GPIO_InitStructure.GPIO_Pin = JOYSTICK_GPIO_SPI_CS;
    GPIO_Init(JOYSTICK_GPIO_SPI_PORT, &GPIO_InitStructure);

    /* SPI SCK pin configuration */
    GPIO_InitStructure.GPIO_Pin = JOYSTICK_GPIO_SPI_SCK;
    GPIO_Init(JOYSTICK_GPIO_SPI_PORT, &GPIO_InitStructure);

    /* SPI MOSI pin configuration */
    GPIO_InitStructure.GPIO_Pin =  JOYSTICK_GPIO_SPI_MOSI;
    GPIO_Init(JOYSTICK_GPIO_SPI_PORT, &GPIO_InitStructure);

    /* SPI MISO pin configuration */
    GPIO_InitStructure.GPIO_Pin = JOYSTICK_GPIO_SPI_MISO;
    GPIO_Init(JOYSTICK_GPIO_SPI_PORT, &GPIO_InitStructure);

    /* SPI configuration -------------------------------------------------------*/
    SPI_I2S_DeInit(JOYSTICK_SPI);
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_Init(JOYSTICK_SPI, &SPI_InitStructure);

    /* Configure the RX FIFO Threshold */
    SPI_RxFIFOThresholdConfig(JOYSTICK_SPI, SPI_RxFIFOThreshold_QF);
    
    /* Enable hardware NSS output */
    SPI_SSOutputCmd(JOYSTICK_SPI, ENABLE);

    /* Configure GPIO PIN for Lis Chip select */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    /* Deselect : Chip Select high */
    GPIO_SetBits(GPIOE, GPIO_Pin_3);

    /* Enable and set SPI1 Interrupt to the assigned priority */
    //NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
    //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_JOYSTICK_PRI;
    //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
    //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //NVIC_Init(&NVIC_InitStructure);

    //SPI_I2S_ITConfig(JOYSTICK_SPI, SPI_I2S_IT_RXNE, ENABLE);

    /* Enable JOYSTICK_SPI  */
    //SPI_Cmd(JOYSTICK_SPI, ENABLE);

    isInit = true;

    return isInit;
}

bool joystick_test(void)
{
    return isInit;
}

/***********************
 * SPI private methods *
 ***********************/
uint8_t spi_send_byte(uint8_t byte)
{
    /* Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(JOYSTICK_SPI, SPI_I2S_FLAG_TXE) == RESET);

    /* Send byte through the SPI1 peripheral */
    SPI_SendData8(JOYSTICK_SPI, byte);

    /* Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(JOYSTICK_SPI, SPI_I2S_FLAG_RXNE) == RESET);

    /* Return the byte read from the SPI bus */
    return SPI_ReceiveData8(JOYSTICK_SPI);
}

uint8_t spi_receive_byte(void)
{
    return spi_send_byte(DUMMY_BYTE);
}
