################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/LCD_i2c.c \
../MCAL/external_interrupts.c \
../MCAL/gpio.c \
../MCAL/i2c.c \
../MCAL/icu.c \
../MCAL/timer0_pwm.c \
../MCAL/uart.c 

OBJS += \
./MCAL/LCD_i2c.o \
./MCAL/external_interrupts.o \
./MCAL/gpio.o \
./MCAL/i2c.o \
./MCAL/icu.o \
./MCAL/timer0_pwm.o \
./MCAL/uart.o 

C_DEPS += \
./MCAL/LCD_i2c.d \
./MCAL/external_interrupts.d \
./MCAL/gpio.d \
./MCAL/i2c.d \
./MCAL/icu.d \
./MCAL/timer0_pwm.d \
./MCAL/uart.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c MCAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\Hesha\Desktop\AMIT_FINAL_PROJECT\Final_Project\LIB" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


