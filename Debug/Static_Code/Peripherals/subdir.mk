################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Static_Code/Peripherals/UART1_Init.c 

OBJS += \
./Static_Code/Peripherals/UART1_Init.o 

C_DEPS += \
./Static_Code/Peripherals/UART1_Init.d 


# Each subdirectory must supply rules for building sources it contributes
Static_Code/Peripherals/%.o: ../Static_Code/Peripherals/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/mauro/Desktop/FRDM22-M1-Backup1 - Copia - Copia - Copia/Static_Code/System" -I"C:/Users/mauro/Desktop/FRDM22-M1-Backup1 - Copia - Copia - Copia/Static_Code/PDD" -I"C:/Users/mauro/Desktop/FRDM22-M1-Backup1 - Copia - Copia - Copia/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/mauro/Desktop/FRDM22-M1-Backup1 - Copia - Copia - Copia/Sources" -I"C:/Users/mauro/Desktop/FRDM22-M1-Backup1 - Copia - Copia - Copia/Generated_Code" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/Repositories/lib/FreeMASTER/FreeMASTER_1_9/src_common" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/Repositories/lib/FreeMASTER/FreeMASTER_1_9/src_platforms/Kxx" -I"C:/Users/mauro/Desktop/FRDM22-M1-Backup1 - Copia - Copia - Copia/Static_Code/Peripherals" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


