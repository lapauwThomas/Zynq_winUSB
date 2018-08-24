################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/main.c \
../src/platform.c \
../src/xusbps_COMMS.c \
../src/xusbps_Ringbuffer.c \
../src/xusbps_ch9.c \
../src/xusbps_ch9_winusb.c 

OBJS += \
./src/main.o \
./src/platform.o \
./src/xusbps_COMMS.o \
./src/xusbps_Ringbuffer.o \
./src/xusbps_ch9.o \
./src/xusbps_ch9_winusb.o 

C_DEPS += \
./src/main.d \
./src/platform.d \
./src/xusbps_COMMS.d \
./src/xusbps_Ringbuffer.d \
./src/xusbps_ch9.d \
./src/xusbps_ch9_winusb.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../USB_example_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


