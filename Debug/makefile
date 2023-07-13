################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include inc/MPU6050/subdir.mk
-include inc/HM11/subdir.mk
-include inc/CRC8/subdir.mk
-include firmware/hal/CortexM3/GNU/subdir.mk
-include firmware/hal/CortexM3/subdir.mk
-include firmware/drivers_config/sys_config/subdir.mk
-include firmware/drivers/mss_sys_services/subdir.mk
-include firmware/drivers/mss_rtc/subdir.mk
-include firmware/drivers/mss_pdma/subdir.mk
-include firmware/drivers/mss_nvm/subdir.mk
-include firmware/drivers/mss_hpdma/subdir.mk
-include firmware/drivers/CoreUARTapb/subdir.mk
-include firmware/drivers/CoreI2C/subdir.mk
-include firmware/CMSIS/startup_gcc/subdir.mk
-include firmware/CMSIS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
BT-Gyro-SW.hex \

SECONDARY_SIZE += \
BT-Gyro-SW.siz \


# All Target
all: BT-Gyro-SW.elf secondary-outputs

# Tool invocations
BT-Gyro-SW.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "C:\Users\Nathan\Desktop\UADL\Internship\Acromax\BT-Gyro\BT-Gyro-SW\firmware\CMSIS\startup_gcc\debug-in-microsemi-smartfusion2-esram.ld" -Xlinker --gc-sections -Wl,-Map,"BT-Gyro-SW.map" --specs=nano.specs -o "BT-Gyro-SW.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

BT-Gyro-SW.hex: BT-Gyro-SW.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "BT-Gyro-SW.elf"  "BT-Gyro-SW.hex"
	@echo 'Finished building: $@'
	@echo ' '

BT-Gyro-SW.siz: BT-Gyro-SW.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "BT-Gyro-SW.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) BT-Gyro-SW.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
