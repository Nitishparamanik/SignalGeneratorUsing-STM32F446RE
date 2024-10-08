################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/gpio.c \
../Src/main.c \
../Src/pll.c \
../Src/serial.c \
../Src/sysTick.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/waveforms.c 

OBJS += \
./Src/adc.o \
./Src/gpio.o \
./Src/main.o \
./Src/pll.o \
./Src/serial.o \
./Src/sysTick.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/waveforms.o 

C_DEPS += \
./Src/adc.d \
./Src/gpio.d \
./Src/main.d \
./Src/pll.d \
./Src/serial.d \
./Src/sysTick.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/waveforms.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc.cyclo ./Src/adc.d ./Src/adc.o ./Src/adc.su ./Src/gpio.cyclo ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/pll.cyclo ./Src/pll.d ./Src/pll.o ./Src/pll.su ./Src/serial.cyclo ./Src/serial.d ./Src/serial.o ./Src/serial.su ./Src/sysTick.cyclo ./Src/sysTick.d ./Src/sysTick.o ./Src/sysTick.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/waveforms.cyclo ./Src/waveforms.d ./Src/waveforms.o ./Src/waveforms.su

.PHONY: clean-Src

