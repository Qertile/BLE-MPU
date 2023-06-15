################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../firmware/drivers/mss_pdma/mss_pdma.c 

OBJS += \
./firmware/drivers/mss_pdma/mss_pdma.o 

C_DEPS += \
./firmware/drivers/mss_pdma/mss_pdma.d 


# Each subdirectory must supply rules for building sources it contributes
firmware/drivers/mss_pdma/%.o: ../firmware/drivers/mss_pdma/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


