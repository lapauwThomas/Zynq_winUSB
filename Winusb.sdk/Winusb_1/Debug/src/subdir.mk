################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/USB_serial.c \
../src/helloworld.c \
../src/platform.c \
../src/xusbps_WINUSB.c \
../src/xusbps_WINUSB_buffer.c \
../src/xusbps_WINUSB_ch9.c \
../src/xusbps_WINUSB_const.c \
../src/xusbps_WINUSB_irq.c 

OBJS += \
./src/USB_serial.o \
./src/helloworld.o \
./src/platform.o \
./src/xusbps_WINUSB.o \
./src/xusbps_WINUSB_buffer.o \
./src/xusbps_WINUSB_ch9.o \
./src/xusbps_WINUSB_const.o \
./src/xusbps_WINUSB_irq.o 

C_DEPS += \
./src/USB_serial.d \
./src/helloworld.d \
./src/platform.d \
./src/xusbps_WINUSB.d \
./src/xusbps_WINUSB_buffer.d \
./src/xusbps_WINUSB_ch9.d \
./src/xusbps_WINUSB_const.d \
./src/xusbps_WINUSB_irq.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../Winusb_1_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


