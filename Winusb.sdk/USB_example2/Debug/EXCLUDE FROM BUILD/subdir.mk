################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../EXCLUDE\ FROM\ BUILD/xusbps_class_winusb.c 

OBJS += \
./EXCLUDE\ FROM\ BUILD/xusbps_class_winusb.o 

C_DEPS += \
./EXCLUDE\ FROM\ BUILD/xusbps_class_winusb.d 


# Each subdirectory must supply rules for building sources it contributes
EXCLUDE\ FROM\ BUILD/xusbps_class_winusb.o: ../EXCLUDE\ FROM\ BUILD/xusbps_class_winusb.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../USB_example_bsp/ps7_cortexa9_0/include -MMD -MP -MF"EXCLUDE FROM BUILD/xusbps_class_winusb.d" -MT"EXCLUDE\ FROM\ BUILD/xusbps_class_winusb.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


