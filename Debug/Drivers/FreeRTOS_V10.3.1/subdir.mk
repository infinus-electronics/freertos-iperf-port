################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/FreeRTOS_V10.3.1/croutine.c \
../Drivers/FreeRTOS_V10.3.1/event_groups.c \
../Drivers/FreeRTOS_V10.3.1/list.c \
../Drivers/FreeRTOS_V10.3.1/queue.c \
../Drivers/FreeRTOS_V10.3.1/stream_buffer.c \
../Drivers/FreeRTOS_V10.3.1/tasks.c \
../Drivers/FreeRTOS_V10.3.1/timers.c 

OBJS += \
./Drivers/FreeRTOS_V10.3.1/croutine.o \
./Drivers/FreeRTOS_V10.3.1/event_groups.o \
./Drivers/FreeRTOS_V10.3.1/list.o \
./Drivers/FreeRTOS_V10.3.1/queue.o \
./Drivers/FreeRTOS_V10.3.1/stream_buffer.o \
./Drivers/FreeRTOS_V10.3.1/tasks.o \
./Drivers/FreeRTOS_V10.3.1/timers.o 

C_DEPS += \
./Drivers/FreeRTOS_V10.3.1/croutine.d \
./Drivers/FreeRTOS_V10.3.1/event_groups.d \
./Drivers/FreeRTOS_V10.3.1/list.d \
./Drivers/FreeRTOS_V10.3.1/queue.d \
./Drivers/FreeRTOS_V10.3.1/stream_buffer.d \
./Drivers/FreeRTOS_V10.3.1/tasks.d \
./Drivers/FreeRTOS_V10.3.1/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/FreeRTOS_V10.3.1/%.o Drivers/FreeRTOS_V10.3.1/%.su Drivers/FreeRTOS_V10.3.1/%.cyclo: ../Drivers/FreeRTOS_V10.3.1/%.c Drivers/FreeRTOS_V10.3.1/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DDATA_IN_D2_SRAM -DSTM32H753xx -DUSE_HAL_DRIVER -DUSE_LOG_EVENT=0 -DLOG_EVENT_COUNT=100 -DLOG_EVENT_NAME_LEN=32 -DEVENT_MAY_WRAP=0 -DSTATIC_LOG_MEMORY=1 -DipconfigUSE_TCP_MEM_STATS=0 -DSYMBOLS_USED=1 -c -I../Core/Inc -I"C:/Users/yehen/STM32CubeIDE/workspace_1.13.2/freertos-iperf-port/Drivers/FreeRTOS-Plus-TCP/source/portable/NetworkInterface/STM32Hxx" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/yehen/STM32CubeIDE/workspace_1.13.2/freertos-iperf-port/Drivers/FreeRTOS_V10.3.1/include" -I"C:/Users/yehen/STM32CubeIDE/workspace_1.13.2/freertos-iperf-port/Drivers/FreeRTOS_V10.3.1/portable/GCC/ARM_CM7/r0p1" -I"C:/Users/yehen/STM32CubeIDE/workspace_1.13.2/freertos-iperf-port/Drivers/Utilities" -I"C:/Users/yehen/STM32CubeIDE/workspace_1.13.2/freertos-iperf-port/Drivers/FreeRTOS-Plus-TCP/include" -I"C:/Users/yehen/STM32CubeIDE/workspace_1.13.2/freertos-iperf-port/Drivers/FreeRTOS-Plus-TCP/source/portable/Compiler/GCC" -I"C:/Users/yehen/STM32CubeIDE/workspace_1.13.2/freertos-iperf-port/Drivers/FreeRTOS-Plus-TCP/source/portable/NetworkInterface/include" -I"C:/Users/yehen/STM32CubeIDE/workspace_1.13.2/freertos-iperf-port/Drivers/FreeRTOS-Plus-TCP/tools/tcp_utilities/include" -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-FreeRTOS_V10-2e-3-2e-1

clean-Drivers-2f-FreeRTOS_V10-2e-3-2e-1:
	-$(RM) ./Drivers/FreeRTOS_V10.3.1/croutine.cyclo ./Drivers/FreeRTOS_V10.3.1/croutine.d ./Drivers/FreeRTOS_V10.3.1/croutine.o ./Drivers/FreeRTOS_V10.3.1/croutine.su ./Drivers/FreeRTOS_V10.3.1/event_groups.cyclo ./Drivers/FreeRTOS_V10.3.1/event_groups.d ./Drivers/FreeRTOS_V10.3.1/event_groups.o ./Drivers/FreeRTOS_V10.3.1/event_groups.su ./Drivers/FreeRTOS_V10.3.1/list.cyclo ./Drivers/FreeRTOS_V10.3.1/list.d ./Drivers/FreeRTOS_V10.3.1/list.o ./Drivers/FreeRTOS_V10.3.1/list.su ./Drivers/FreeRTOS_V10.3.1/queue.cyclo ./Drivers/FreeRTOS_V10.3.1/queue.d ./Drivers/FreeRTOS_V10.3.1/queue.o ./Drivers/FreeRTOS_V10.3.1/queue.su ./Drivers/FreeRTOS_V10.3.1/stream_buffer.cyclo ./Drivers/FreeRTOS_V10.3.1/stream_buffer.d ./Drivers/FreeRTOS_V10.3.1/stream_buffer.o ./Drivers/FreeRTOS_V10.3.1/stream_buffer.su ./Drivers/FreeRTOS_V10.3.1/tasks.cyclo ./Drivers/FreeRTOS_V10.3.1/tasks.d ./Drivers/FreeRTOS_V10.3.1/tasks.o ./Drivers/FreeRTOS_V10.3.1/tasks.su ./Drivers/FreeRTOS_V10.3.1/timers.cyclo ./Drivers/FreeRTOS_V10.3.1/timers.d ./Drivers/FreeRTOS_V10.3.1/timers.o ./Drivers/FreeRTOS_V10.3.1/timers.su

.PHONY: clean-Drivers-2f-FreeRTOS_V10-2e-3-2e-1

