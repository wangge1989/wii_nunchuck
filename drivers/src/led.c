/**
 * led.c - LED handing functions
 */
#include "led.h"

#include <stdbool.h>
#include "stm32f30x.h"

/*FreeRtos includes*/
#include "FreeRTOS.h"
#include "task.h"

static bool isInit = false;

static GPIO_TypeDef* led_port[] =
{
    [LED_GREEN] = LED_GPIO_PORT,
    [LED_RED]   = LED_GPIO_PORT,
};
static unsigned int led_pin[] =
{
    [LED_GREEN] = LED_GPIO_GREEN,
    [LED_RED]   = LED_GPIO_RED,
};
static int led_polarity[] =
{
    [LED_GREEN] = LED_POL_GREEN,
    [LED_RED]   = LED_POL_RED,
};

//Initialize the green led pin as output
void ledInit()
{
    if (isInit)
        return;

    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIOE Periph clock enable */
    RCC_AHBPeriphClockCmd(LED_GPIO_PERIF, ENABLE);

    /* Configure PE14 and PE15 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = LED_GPIO_GREEN | LED_GPIO_RED;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);

    //Turn off the LED:s
    ledSet(LED_GREEN, 0);
    ledSet(LED_RED, 0);

    isInit = true;
}

bool ledTest(void)
{
    return isInit;
}

void ledSet(led_t led, bool value)
{
    if (led>LED_NUM)
        return;

    if (led_polarity[led]==LED_POL_NEG)
        value = !value;

    if (value)
        GPIO_SetBits(led_port[led], led_pin[led]);
    else
        GPIO_ResetBits(led_port[led], led_pin[led]);
}
