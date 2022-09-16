################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCU1_main.c \
../Timer0.c \
../gpio.c \
../keypad.c \
../lcd.c \
../main_functions_1.c \
../uart_driver.c 

OBJS += \
./MCU1_main.o \
./Timer0.o \
./gpio.o \
./keypad.o \
./lcd.o \
./main_functions_1.o \
./uart_driver.o 

C_DEPS += \
./MCU1_main.d \
./Timer0.d \
./gpio.d \
./keypad.d \
./lcd.d \
./main_functions_1.d \
./uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


