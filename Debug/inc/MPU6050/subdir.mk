################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../inc/MPU6050/mpu6050.c \
../inc/MPU6050/mpu6050_ut.c 

OBJS += \
./inc/MPU6050/mpu6050.o \
./inc/MPU6050/mpu6050_ut.o 

C_DEPS += \
./inc/MPU6050/mpu6050.d \
./inc/MPU6050/mpu6050_ut.d 


# Each subdirectory must supply rules for building sources it contributes
inc/MPU6050/%.o: ../inc/MPU6050/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


