/**
 * joystick.h - JOYSTICK functions header file
 */
#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <stdbool.h>
#include <stdint.h>

#include "stm32f30x.h"

/* Defines for the I2C and GPIO pins used to drive the I2C JOYSTICK*/

#define JOYSTICK_I2C                     I2C1
#define JOYSTICK_I2C_CLK                 RCC_APB1Periph_I2C1
#define JOYSTICK_GPIO_I2C_PORT           GPIOB
#define JOYSTICK_GPIO_I2C_CLK            RCC_AHBPeriph_GPIOB
#define JOYSTICK_GPIO_I2C_SCL            GPIO_Pin_6
#define JOYSTICK_GPIO_I2C_SDA            GPIO_Pin_7
#define JOYSTICK_GPIO_I2C_SCL_SOURCE     GPIO_PinSource6
#define JOYSTICK_GPIO_SPI_SDA_SOURCE     GPIO_PinSource7
#define JOYSTICK_GPIO_SPI_AF             GPIO_AF_4

// Init and test of the connection to the hardware
bool joystick_init(void);
bool joystick_test(void);

void i2c_interrupt_handler(void);

/* Low level reg access
 * FIXME: the user should not need to access raw registers...
 */
uint8_t joystick_write(uint8_t device_addr, uint8_t reg_addr, uint8_t* p_buffer, uint16_t num_byte_to_write);
uint8_t joystick_read(uint8_t device_addr, uint8_t reg_addr, uint8_t* p_buffer, uint16_t num_byte_to_read);

#endif
