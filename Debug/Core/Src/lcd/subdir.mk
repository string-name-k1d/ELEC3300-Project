################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/lcd/display.c \
../Core/Src/lcd/lcd.c 

OBJS += \
./Core/Src/lcd/display.o \
./Core/Src/lcd/lcd.o 

C_DEPS += \
./Core/Src/lcd/display.d \
./Core/Src/lcd/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/lcd/%.o Core/Src/lcd/%.su: ../Core/Src/lcd/%.c Core/Src/lcd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -DSTM32_THREAD_SAFE_STRATEGY=1 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-lcd

clean-Core-2f-Src-2f-lcd:
	-$(RM) ./Core/Src/lcd/display.d ./Core/Src/lcd/display.o ./Core/Src/lcd/display.su ./Core/Src/lcd/lcd.d ./Core/Src/lcd/lcd.o ./Core/Src/lcd/lcd.su

.PHONY: clean-Core-2f-Src-2f-lcd

