################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/expanders/MCP23xxx.cpp \
../Src/expanders/TI95xx.cpp \
../Src/expanders/expanders.cpp 

OBJS += \
./Src/expanders/MCP23xxx.o \
./Src/expanders/TI95xx.o \
./Src/expanders/expanders.o 

CPP_DEPS += \
./Src/expanders/MCP23xxx.d \
./Src/expanders/TI95xx.d \
./Src/expanders/expanders.d 


# Each subdirectory must supply rules for building sources it contributes
Src/expanders/MCP23xxx.o: ../Src/expanders/MCP23xxx.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions -fstack-usage -MMD -MP -MF"Src/expanders/MCP23xxx.d" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/expanders/TI95xx.o: ../Src/expanders/TI95xx.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions -fstack-usage -MMD -MP -MF"Src/expanders/TI95xx.d" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/expanders/expanders.o: ../Src/expanders/expanders.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions -fstack-usage -MMD -MP -MF"Src/expanders/expanders.d" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

