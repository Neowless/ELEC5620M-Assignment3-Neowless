################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../My_LCD.c \
../Test.c \
../main.c 

C_DEPS += \
./My_LCD.d \
./Test.d \
./main.d 

OBJS += \
./My_LCD.o \
./Test.o \
./main.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc --cpu=Cortex-A9.no_neon --apcs=/hardfp --arm -I"C:\Users\Neowless\Desktop\Workspace\ELEC5620M-Resources\Drivers" -O3 -Otime --loop_optimization_level=2 -g --md --depend_format=unix_escaped --no_depend_system_headers -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


