################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../firmware/drivers_config/sys_config/sys_config.c 

OBJS += \
./firmware/drivers_config/sys_config/sys_config.o 

C_DEPS += \
./firmware/drivers_config/sys_config/sys_config.d 


# Each subdirectory must supply rules for building sources it contributes
firmware/drivers_config/sys_config/%.o: ../firmware/drivers_config/sys_config/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


