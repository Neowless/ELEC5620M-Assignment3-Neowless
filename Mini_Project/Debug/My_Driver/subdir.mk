################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../My_Driver/Audio_Out.c \
../My_Driver/Syphony.c \
../My_Driver/XYSeldon.c 

C_DEPS += \
./My_Driver/Audio_Out.d \
./My_Driver/Syphony.d \
./My_Driver/XYSeldon.d 

OBJS += \
./My_Driver/Audio_Out.o \
./My_Driver/Syphony.o \
./My_Driver/XYSeldon.o 


# Each subdirectory must supply rules for building sources it contributes
My_Driver/%.o: ../My_Driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc --cpu=Cortex-A9.no_neon --apcs=/hardfp --arm -I"C:\Users\Neowless\Desktop\Workspace\ELEC5620M-Resources\Drivers" -O3 -Otime --loop_optimization_level=2 -g --md --depend_format=unix_escaped --no_depend_system_headers --depend_dir="My_Driver" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


