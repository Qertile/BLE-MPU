################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../firmware/drivers/mss_nvm/mss_nvm.c 

OBJS += \
./firmware/drivers/mss_nvm/mss_nvm.o 

C_DEPS += \
./firmware/drivers/mss_nvm/mss_nvm.d 


# Each subdirectory must supply rules for building sources it contributes
firmware/drivers/mss_nvm/%.o: ../firmware/drivers/mss_nvm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


