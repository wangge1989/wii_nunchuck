/**
 * nvicconf.h - Interrupt priority configuration
 *
 * The STM32 has 16 priorities to choose from where 0 is the
 * highest priority. They are now configured using no groups.
 *
 * Interrupt functions that call FreeRTOS FromISR functions
 * must have a interrupt number 10 and above which is currently
 * set by configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#ifndef NVIC_CONF_H_
#define NVIC_CONF_H_

#define NVIC_NO_GROUPS        NVIC_PriorityGroup_0

#define NVIC_I2C_PRI          (5)
#define NVIC_UART_PRI         (6)
#define NVIC_TRACE_TIM_PRI    (7)
#define NVIC_ADC_PRI          (12)
#define NVIC_JOYSTICK_PRI     (13)

#endif /* NVIC_CONF_H_ */
