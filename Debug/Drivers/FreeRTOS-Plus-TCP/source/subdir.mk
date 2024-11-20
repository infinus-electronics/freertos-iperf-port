################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_ARP.c \
../Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_DHCP.c \
../Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_DNS.c \
../Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_IP.c \
../Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_Sockets.c \
../Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_Stream_Buffer.c \
../Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_TCP_IP.c \
../Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_TCP_WIN.c \
../Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_UDP_IP.c 

OBJS += \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_ARP.o \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_DHCP.o \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_DNS.o \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_IP.o \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_Sockets.o \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_Stream_Buffer.o \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_TCP_IP.o \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_TCP_WIN.o \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_UDP_IP.o 

C_DEPS += \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_ARP.d \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_DHCP.d \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_DNS.d \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_IP.d \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_Sockets.d \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_Stream_Buffer.d \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_TCP_IP.d \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_TCP_WIN.d \
./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_UDP_IP.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/FreeRTOS-Plus-TCP/source/%.o Drivers/FreeRTOS-Plus-TCP/source/%.su Drivers/FreeRTOS-Plus-TCP/source/%.cyclo: ../Drivers/FreeRTOS-Plus-TCP/source/%.c Drivers/FreeRTOS-Plus-TCP/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32H753xx -DUSE_HAL_DRIVER -DUSE_LOG_EVENT=0 -DLOG_EVENT_COUNT=100 -DLOG_EVENT_NAME_LEN=32 -DEVENT_MAY_WRAP=0 -DSTATIC_LOG_MEMORY=1 -DipconfigUSE_TCP_MEM_STATS=0 -DSYMBOLS_USED=1 -c -I../Core/Inc -I"C:/Users/yehen/STM32CubeIDE/workspace_1.13.2/freertos-iperf-port/Drivers/FreeRTOS-Plus-TCP/source/portable/NetworkInterface/STM32Hxx" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/yehen/STM32CubeIDE/workspace_1.13.2/freertos-iperf-port/Drivers/FreeRTOS_V10.3.1/include" -I"C:/Users/yehen/STM32CubeIDE/workspace_1.13.2/freertos-iperf-port/Drivers/FreeRTOS_V10.3.1/portable/GCC/ARM_CM7/r0p1" -I"C:/Users/yehen/STM32CubeIDE/workspace_1.13.2/freertos-iperf-port/Drivers/Utilities" -I"C:/Users/yehen/STM32CubeIDE/workspace_1.13.2/freertos-iperf-port/Drivers/FreeRTOS-Plus-TCP/include" -I"C:/Users/yehen/STM32CubeIDE/workspace_1.13.2/freertos-iperf-port/Drivers/FreeRTOS-Plus-TCP/source/portable/Compiler/GCC" -I"C:/Users/yehen/STM32CubeIDE/workspace_1.13.2/freertos-iperf-port/Drivers/FreeRTOS-Plus-TCP/source/portable/NetworkInterface/include" -I"C:/Users/yehen/STM32CubeIDE/workspace_1.13.2/freertos-iperf-port/Drivers/FreeRTOS-Plus-TCP/tools/tcp_utilities/include" -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-FreeRTOS-2d-Plus-2d-TCP-2f-source

clean-Drivers-2f-FreeRTOS-2d-Plus-2d-TCP-2f-source:
	-$(RM) ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_ARP.cyclo ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_ARP.d ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_ARP.o ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_ARP.su ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_DHCP.cyclo ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_DHCP.d ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_DHCP.o ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_DHCP.su ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_DNS.cyclo ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_DNS.d ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_DNS.o ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_DNS.su ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_IP.cyclo ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_IP.d ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_IP.o ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_IP.su ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_Sockets.cyclo ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_Sockets.d ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_Sockets.o ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_Sockets.su ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_Stream_Buffer.cyclo ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_Stream_Buffer.d ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_Stream_Buffer.o ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_Stream_Buffer.su ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_TCP_IP.cyclo ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_TCP_IP.d ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_TCP_IP.o ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_TCP_IP.su ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_TCP_WIN.cyclo ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_TCP_WIN.d ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_TCP_WIN.o ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_TCP_WIN.su ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_UDP_IP.cyclo ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_UDP_IP.d ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_UDP_IP.o ./Drivers/FreeRTOS-Plus-TCP/source/FreeRTOS_UDP_IP.su

.PHONY: clean-Drivers-2f-FreeRTOS-2d-Plus-2d-TCP-2f-source

