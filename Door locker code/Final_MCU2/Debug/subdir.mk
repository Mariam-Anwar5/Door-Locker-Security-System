################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../MCU2_main.c \
../Timer0.c \
../external_eeprom.c \
../gpio.c \
../lcd.c \
../main_functions_2.c \
../motor_driver.c \
../twi.c \
../uart_driver.c 

OBJS += \
./Buzzer.o \
./MCU2_main.o \
./Timer0.o \
./external_eeprom.o \
./gpio.o \
./lcd.o \
./main_functions_2.o \
./motor_driver.o \
./twi.o \
./uart_driver.o 

C_DEPS += \
./Buzzer.d \
./MCU2_main.d \
./Timer0.d \
./external_eeprom.d \
./gpio.d \
./lcd.d \
./main_functions_2.d \
./motor_driver.d \
./twi.d \
./uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


