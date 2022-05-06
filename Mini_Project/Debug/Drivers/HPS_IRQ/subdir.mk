################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Neowless/Workspace/ELEC5620M-Resources/Drivers/HPS_IRQ/HPS_IRQ.c 

C_DEPS += \
./Drivers/HPS_IRQ/HPS_IRQ.d 

OBJS += \
./Drivers/HPS_IRQ/HPS_IRQ.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/HPS_IRQ/HPS_IRQ.o: C:/Users/Neowless/Workspace/ELEC5620M-Resources/Drivers/HPS_IRQ/HPS_IRQ.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc --cpu=Cortex-A9.no_neon --apcs=/hardfp --arm -I"C:\Users\Neowless\Desktop\Workspace\ELEC5620M-Resources\Drivers" -O3 -Otime --loop_optimization_level=2 -g --md --depend_format=unix_escaped --no_depend_system_headers --depend_dir="Drivers/HPS_IRQ" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


