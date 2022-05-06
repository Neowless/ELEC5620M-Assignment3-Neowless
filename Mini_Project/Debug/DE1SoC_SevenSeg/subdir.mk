################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DE1SoC_SevenSeg/DE1SoC_SevenSeg.c 

C_DEPS += \
./DE1SoC_SevenSeg/DE1SoC_SevenSeg.d 

OBJS += \
./DE1SoC_SevenSeg/DE1SoC_SevenSeg.o 


# Each subdirectory must supply rules for building sources it contributes
DE1SoC_SevenSeg/%.o: ../DE1SoC_SevenSeg/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc --cpu=Cortex-A9.no_neon --apcs=/hardfp --arm -I"C:\Users\Neowless\Desktop\Workspace\ELEC5620M-Resources\Drivers" -O3 -Otime --loop_optimization_level=2 -g --md --depend_format=unix_escaped --no_depend_system_headers --depend_dir="DE1SoC_SevenSeg" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


