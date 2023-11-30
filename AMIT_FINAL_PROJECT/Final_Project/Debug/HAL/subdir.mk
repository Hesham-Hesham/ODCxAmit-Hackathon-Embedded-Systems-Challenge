################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/dc_motor.c \
../HAL/gps.c \
../HAL/ir_proximity.c \
../HAL/servo.c \
../HAL/ultrasonic_HCSR04.c 

OBJS += \
./HAL/dc_motor.o \
./HAL/gps.o \
./HAL/ir_proximity.o \
./HAL/servo.o \
./HAL/ultrasonic_HCSR04.o 

C_DEPS += \
./HAL/dc_motor.d \
./HAL/gps.d \
./HAL/ir_proximity.d \
./HAL/servo.d \
./HAL/ultrasonic_HCSR04.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c HAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\Hesha\Desktop\AMIT_FINAL_PROJECT\Final_Project\LIB" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


