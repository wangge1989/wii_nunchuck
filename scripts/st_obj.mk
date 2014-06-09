# st_obj.mk - Selection of the ST library objects to compile
# This file is part of the Crazy Flie control program
# Copyright (c) 2009, EAT-IT

VPATH+=$(STLIB)/STM32F30x_StdPeriph_Driver/src/
ST_OBJ=
#ST_OBJ+=stm32f30x_adc.o
#ST_OBJ+=stm32f30x_can.o
#ST_OBJ+=stm32f30x_comp.o
#ST_OBJ+=stm32f30x_crc.o
#ST_OBJ+=stm32f30x_dac.o
#ST_OBJ+=stm32f30x_dbgmcu.o
#ST_OBJ+=stm32f30x_dma.o
#ST_OBJ+=stm32f30x_exti.o
ST_OBJ+=stm32f30x_flash.o
ST_OBJ+=stm32f30x_gpio.o
#ST_OBJ+=stm32f30x_i2c.o
#ST_OBJ+=stm32f30x_iwdg.o
#ST_OBJ+=stm32f30x_misc.o
#ST_OBJ+=stm32f30x_opamp.o
#ST_OBJ+=stm32f30x_pwr.o
ST_OBJ+=stm32f30x_rcc.o
#ST_OBJ+=stm32f30x_rtc.o
ST_OBJ+=stm32f30x_spi.o
#ST_OBJ+=stm32f30x_syscfg.o
#ST_OBJ+=stm32f30x_tim.o
#ST_OBJ+=stm32f30x_usart.o
#ST_OBJ+=stm32f30x_wwdg.o
