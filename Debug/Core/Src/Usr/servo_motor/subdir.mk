################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Usr/servo_motor/servo_motor.c 

OBJS += \
./Core/Src/Usr/servo_motor/servo_motor.o 

C_DEPS += \
./Core/Src/Usr/servo_motor/servo_motor.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Usr/servo_motor/%.o Core/Src/Usr/servo_motor/%.su: ../Core/Src/Usr/servo_motor/%.c Core/Src/Usr/servo_motor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -DSTM32_THREAD_SAFE_STRATEGY=1 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Usr-2f-servo_motor

clean-Core-2f-Src-2f-Usr-2f-servo_motor:
	-$(RM) ./Core/Src/Usr/servo_motor/servo_motor.d ./Core/Src/Usr/servo_motor/servo_motor.o ./Core/Src/Usr/servo_motor/servo_motor.su

.PHONY: clean-Core-2f-Src-2f-Usr-2f-servo_motor

