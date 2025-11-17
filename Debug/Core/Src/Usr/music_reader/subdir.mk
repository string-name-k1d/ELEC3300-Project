################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Usr/music_reader/midi_reader.c 

OBJS += \
./Core/Src/Usr/music_reader/midi_reader.o 

C_DEPS += \
./Core/Src/Usr/music_reader/midi_reader.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Usr/music_reader/%.o Core/Src/Usr/music_reader/%.su: ../Core/Src/Usr/music_reader/%.c Core/Src/Usr/music_reader/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -DSTM32_THREAD_SAFE_STRATEGY=1 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Usr-2f-music_reader

clean-Core-2f-Src-2f-Usr-2f-music_reader:
	-$(RM) ./Core/Src/Usr/music_reader/midi_reader.d ./Core/Src/Usr/music_reader/midi_reader.o ./Core/Src/Usr/music_reader/midi_reader.su

.PHONY: clean-Core-2f-Src-2f-Usr-2f-music_reader

