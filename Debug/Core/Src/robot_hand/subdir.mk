################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/robot_hand/hand_control.c 

OBJS += \
./Core/Src/robot_hand/hand_control.o 

C_DEPS += \
./Core/Src/robot_hand/hand_control.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/robot_hand/%.o Core/Src/robot_hand/%.su: ../Core/Src/robot_hand/%.c Core/Src/robot_hand/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -DSTM32_THREAD_SAFE_STRATEGY=1 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-robot_hand

clean-Core-2f-Src-2f-robot_hand:
	-$(RM) ./Core/Src/robot_hand/hand_control.d ./Core/Src/robot_hand/hand_control.o ./Core/Src/robot_hand/hand_control.su

.PHONY: clean-Core-2f-Src-2f-robot_hand

