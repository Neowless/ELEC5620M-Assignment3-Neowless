################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Neowless/Workspace/ELEC5620M-Resources/Drivers/FatFS/diskio_cyclonev.c \
C:/Users/Neowless/Workspace/ELEC5620M-Resources/Drivers/FatFS/ff.c \
C:/Users/Neowless/Workspace/ELEC5620M-Resources/Drivers/FatFS/ffsystem.c \
C:/Users/Neowless/Workspace/ELEC5620M-Resources/Drivers/FatFS/ffunicode.c 

C_DEPS += \
./Drivers/FatFS/diskio_cyclonev.d \
./Drivers/FatFS/ff.d \
./Drivers/FatFS/ffsystem.d \
./Drivers/FatFS/ffunicode.d 

OBJS += \
./Drivers/FatFS/diskio_cyclonev.o \
./Drivers/FatFS/ff.o \
./Drivers/FatFS/ffsystem.o \
./Drivers/FatFS/ffunicode.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/FatFS/diskio_cyclonev.o: C:/Users/Neowless/Workspace/ELEC5620M-Resources/Drivers/FatFS/diskio_cyclonev.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc --cpu=Cortex-A9.no_neon --apcs=/hardfp --arm -I"C:\Users\Neowless\Desktop\Workspace\ELEC5620M-Resources\Drivers" -O3 -Otime --loop_optimization_level=2 -g --md --depend_format=unix_escaped --no_depend_system_headers --depend_dir="Drivers/FatFS" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/FatFS/ff.o: C:/Users/Neowless/Workspace/ELEC5620M-Resources/Drivers/FatFS/ff.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc --cpu=Cortex-A9.no_neon --apcs=/hardfp --arm -I"C:\Users\Neowless\Desktop\Workspace\ELEC5620M-Resources\Drivers" -O3 -Otime --loop_optimization_level=2 -g --md --depend_format=unix_escaped --no_depend_system_headers --depend_dir="Drivers/FatFS" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/FatFS/ffsystem.o: C:/Users/Neowless/Workspace/ELEC5620M-Resources/Drivers/FatFS/ffsystem.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc --cpu=Cortex-A9.no_neon --apcs=/hardfp --arm -I"C:\Users\Neowless\Desktop\Workspace\ELEC5620M-Resources\Drivers" -O3 -Otime --loop_optimization_level=2 -g --md --depend_format=unix_escaped --no_depend_system_headers --depend_dir="Drivers/FatFS" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/FatFS/ffunicode.o: C:/Users/Neowless/Workspace/ELEC5620M-Resources/Drivers/FatFS/ffunicode.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc --cpu=Cortex-A9.no_neon --apcs=/hardfp --arm -I"C:\Users\Neowless\Desktop\Workspace\ELEC5620M-Resources\Drivers" -O3 -Otime --loop_optimization_level=2 -g --md --depend_format=unix_escaped --no_depend_system_headers --depend_dir="Drivers/FatFS" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


