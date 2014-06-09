/**
 * joystick.h - JOYSTICK functions header file
 */
#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <stdbool.h>
#include <stdint.h>

#include "stm32f30x.h"

/* Defines for the SPI and GPIO pins used to drive the SPI JOYSTICK*/

#define JOYSTICK_SPI                     SPI1
#define JOYSTICK_SPI_CLK                 RCC_APB2Periph_SPI1
#define JOYSTICK_GPIO_SPI_PORT           GPIOA
#define JOYSTICK_GPIO_SPI_CLK            RCC_AHBPeriph_GPIOA
#define JOYSTICK_GPIO_SPI_CS             GPIO_Pin_4
#define JOYSTICK_GPIO_SPI_SCK            GPIO_Pin_5
#define JOYSTICK_GPIO_SPI_MISO           GPIO_Pin_6
#define JOYSTICK_GPIO_SPI_MOSI           GPIO_Pin_7
#define JOYSTICK_GPIO_SPI_CS_SOURCE      GPIO_PinSource4
#define JOYSTICK_GPIO_SPI_SCK_SOURCE     GPIO_PinSource5
#define JOYSTICK_GPIO_SPI_MISO_SOURCE    GPIO_PinSource6
#define JOYSTICK_GPIO_SPI_MOSI_SOURCE    GPIO_PinSource7
#define JOYSTICK_GPIO_SPI_AF             GPIO_AF_5

#define DUMMY_BYTE                       0x00

// Init and test of the connection to the hardware
bool joystick_init(void);
bool joystick_test(void);

void spi_interrupt_handler(void);

/* Low level reg access
 * FIXME: the user should not need to access raw registers...
 */
uint8_t spi_send_byte(uint8_t byte);
uint8_t spi_receive_byte(void);

#endif
