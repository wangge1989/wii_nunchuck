# CrazyFlie's Makefile
# Copyright (c) 2011,2012 Bitcraze AB
# This Makefile compiles all the object file to ./bin/ and the resulting firmware
# image in ./cflie.elf and ./cflie.bin

#Put your personal build config in config.mk and DO NOT COMMIT IT!
#-include config.mk

######### JTAG and environment configuration ##########
CROSS_COMPILE     ?= arm-none-eabi-
PYTHON2           ?= python
DEBUG             ?= 1

## Flag that can be added to config.mk
# CFLAGS += -DUSE_UART_CRTP        # Set CRTP link to UART
# CFLAGS += -DUSE_ESKYLINK         # Set CRTP link to E-SKY receiver
# CFLAGS += -DENABLE_UART          # To enable the uart
# CFLAGS += -DDEBUG_PRINT_ON_UART  # Redirect the console output to the UART

REV               ?= A

############### Location configuration ################
FREERTOS = lib/FreeRTOS
PORT = $(FREERTOS)/portable/GCC/ARM_CM4F
STLIB = lib/

################ Build configuration ##################
# St Lib
VPATH += $(STLIB)/CMSIS\Device\ST\STM32F30x\Source
CRT0 = startup_stm32f30x.o

include scripts/st_obj.mk

# FreeRTOS
VPATH += $(PORT)
PORT_OBJ = port.o
VPATH +=  $(FREERTOS)/portable/MemMang
MEMMANG_OBJ = heap_4.o

VPATH += $(FREERTOS)
FREERTOS_OBJ = list.o tasks.o queue.o timers.o $(MEMMANG_OBJ)

# Project
VPATH += init hal/src modules/src utils/src drivers/src

############### Source files configuration ################

# Init
PROJ_OBJ = main.o system_stm32f30x.o

# Drivers
PROJ_OBJ += stm32f30x_it.o led.o joystick.o

# Hal
PROJ_OBJ += ledseq.o
#PROJ_OBJ += crtp.o ledseq.o freeRTOSdebug.o imu.o pm.o radiolink.o eskylink.o
#PROJ_OBJ += usec_time.o

# Modules
PROJ_OBJ += system.o
#PROJ_OBJ += system.o comm.o console.o pid.o crtpservice.o param.o
#PROJ_OBJ += commander.o controller.o sensfusion6.o stabilizer.o
#PROJ_OBJ += log.o worker.o

# Utilities
#PROJ_OBJ += filter.o cpuid.o cfassert.o configblock.o eprintf.o crc.o fp16.o debug.o abort.o
#PROJ_OBJ += version.o


OBJ = $(CRT0) $(FREERTOS_OBJ) $(PORT_OBJ) $(ST_OBJ) $(PROJ_OBJ)

ifdef P
  C_PROFILE = -D P_$(P)
endif

############### Compilation configuration ################
AS = $(CROSS_COMPILE)as
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)gcc
SIZE = $(CROSS_COMPILE)size
OBJCOPY = $(CROSS_COMPILE)objcopy

INCLUDES  = -I$(FREERTOS)/include -I$(PORT) -I.
INCLUDES += -I$(STLIB)/STM32F30x_StdPeriph_Driver/inc
INCLUDES += -I$(STLIB)/CMSIS/Device/ST/STM32F30x/Include
INCLUDES += -I$(STLIB)/CMSIS/Include
INCLUDES += -Iconfig -Ihal/interface -Imodules/interface
INCLUDES += -Iutils/interface -Idrivers/interface
INCLUDES += -Iinit

PROCESSOR = -mlittle-endian -mcpu=cortex-m4  -march=armv7e-m -mthumb 
PROCESSOR += -mfpu=fpv4-sp-d16 -mfloat-abi=hard


#Flags required by the ST library
STFLAGS = -DUSE_STDPERIPH_DRIVER -DSTM32F30X

ifeq ($(DEBUG), 1)
  CFLAGS += -O0 -g3
else
  CFLAGS += -Os -g3
endif

ifeq ($(LTO), 1)
  CFLAGS += -flto -fuse-linker-plugin
endif

CFLAGS += -DBOARD_REV_$(REV)

CFLAGS += $(PROCESSOR) $(INCLUDES) $(STFLAGS) -Wall -fno-strict-aliasing $(C_PROFILE)
# Compiler flags to generate dependency files:
CFLAGS += -MD -MP -MF $(BIN)/dep/$(@).d -MQ $(@)
#Permits to remove un-used functions and global variables from output file
CFLAGS += -ffunction-sections -fdata-sections

ASFLAGS = $(PROCESSOR) $(INCLUDES)
LDFLAGS = $(CFLAGS) -Wl,-Map=$(PROG).map,--cref,--gc-sections -nostdlib
LDFLAGS += -T scripts/stm32f30x_20k_128k_flash.ld

#Program name
PROG = wii_nunchuck

#Where to compile the .o
BIN = bin
VPATH += $(BIN)

#Dependency files to include
DEPS := $(foreach o,$(OBJ),$(BIN)/dep/$(o).d)

##################### Misc. ################################
ifeq ($(SHELL),C:/Git/bin/sh.exe)
  COL_RED=\033[1;31m
  COL_GREEN=\033[1;32m
  COL_RESET=\033[m
endif

#################### Targets ###############################

all: build
build: compile size
compile: $(PROG).hex $(PROG).bin

size: compile
	@$(SIZE) -B $(PROG).elf

#Print preprocessor #defines
prep:
	@$(CC) -dD

include scripts/targets.mk

#include dependencies
#-include $(DEPS)
