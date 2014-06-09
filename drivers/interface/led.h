/**
 * led.h - LED functions header file
 */
#ifndef __LED_H__
#define __LED_H__

#include <stdbool.h>

#include "stm32f30x.h"

//Led polarity configuration constant
#define LED_POL_POS 0
#define LED_POL_NEG 1

//Hardware configuration
#define LED_GPIO_PERIF    RCC_AHBPeriph_GPIOE
#define LED_GPIO_PORT     GPIOE
#define LED_GPIO_GREEN    GPIO_Pin_15
#define LED_POL_GREEN     LED_POL_POS
#define LED_GPIO_RED      GPIO_Pin_13
#define LED_POL_RED       LED_POL_POS

#define LED_NUM           2

typedef enum {LED_RED=0, LED_GREEN} led_t;

void ledInit();
bool ledTest();

// Procedures to set the status of the LEDs
void ledSet(led_t led, bool value);

void ledTask(void *param);

//Legacy functions
#define ledSetRed(VALUE) ledSet(LED_RED, VALUE)
#define ledSetGreen(VALUE) ledSet(LED_GREEN, VALUE)

#endif
