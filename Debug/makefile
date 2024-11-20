################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/Utilities/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
-include Drivers/FreeRTOS_V10.3.1/portable/MemMang/subdir.mk
-include Drivers/FreeRTOS_V10.3.1/portable/GCC/ARM_CM7/r0p1/subdir.mk
-include Drivers/FreeRTOS_V10.3.1/subdir.mk
-include Drivers/FreeRTOS-Plus-TCP/tools/tcp_utilities/subdir.mk
-include Drivers/FreeRTOS-Plus-TCP/source/portable/NetworkInterface/STM32Hxx/subdir.mk
-include Drivers/FreeRTOS-Plus-TCP/source/portable/NetworkInterface/Common/subdir.mk
-include Drivers/FreeRTOS-Plus-TCP/source/portable/BufferManagement/subdir.mk
-include Drivers/FreeRTOS-Plus-TCP/source/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := freertos-iperf-port
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
freertos-iperf-port.elf \

MAP_FILES += \
freertos-iperf-port.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
freertos-iperf-port.list \


# All Target
all: main-build

# Main-build Target
main-build: freertos-iperf-port.elf secondary-outputs

# Tool invocations
freertos-iperf-port.elf freertos-iperf-port.map: $(OBJS) $(USER_OBJS) C:\Users\yehen\STM32CubeIDE\workspace_1.13.2\freertos-iperf-port\STM32H753ZITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "freertos-iperf-port.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\yehen\STM32CubeIDE\workspace_1.13.2\freertos-iperf-port\STM32H753ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="freertos-iperf-port.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

freertos-iperf-port.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "freertos-iperf-port.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout freertos-iperf-port.elf freertos-iperf-port.list freertos-iperf-port.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
