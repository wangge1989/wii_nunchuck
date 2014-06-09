# This file is a init script for gdb debugger

target remote localhost:4242

#monitor speed Auto
#monitor flash device = STM32F303VC
#monitor breakpoints = 1
#monitor flash download = 1

file ps2joystick.elf
load

# Reset the target
monitor reset 0

b systemTask

c