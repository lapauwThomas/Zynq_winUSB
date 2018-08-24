################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/platform.c \
../src/xusbps_ch9.c \
../src/xusbps_ch9_storage.c \
../src/xusbps_class_storage.c \
../src/xusbps_intr_example.c 

OBJS += \
./src/platform.o \
./src/xusbps_ch9.o \
./src/xusbps_ch9_storage.o \
./src/xusbps_class_storage.o \
./src/xusbps_intr_example.o 

C_DEPS += \
./src/platform.d \
./src/xusbps_ch9.d \
./src/xusbps_ch9_storage.d \
./src/xusbps_class_storage.d \
./src/xusbps_intr_example.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../USB_example_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


