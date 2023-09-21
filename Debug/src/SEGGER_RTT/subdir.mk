################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/SEGGER_RTT/SEGGER_RTT.c \
../src/SEGGER_RTT/SEGGER_RTT_printf.c 

OBJS += \
./src/SEGGER_RTT/SEGGER_RTT.o \
./src/SEGGER_RTT/SEGGER_RTT_printf.o 

C_DEPS += \
./src/SEGGER_RTT/SEGGER_RTT.d \
./src/SEGGER_RTT/SEGGER_RTT_printf.d 


# Each subdirectory must supply rules for building sources it contributes
src/SEGGER_RTT/%.o: ../src/SEGGER_RTT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -D_RENESAS_RA_ -D_RA_CORE=CM4 -I"C:\Users\sandeep.mk\e2_studio\Working projects\GY-521\ra\fsp\inc" -I"C:\Users\sandeep.mk\e2_studio\Working projects\GY-521\ra\fsp\inc\api" -I"C:\Users\sandeep.mk\e2_studio\Working projects\GY-521\ra\fsp\inc\instances" -I"C:\Users\sandeep.mk\e2_studio\Working projects\GY-521\ra\arm\CMSIS_5\CMSIS\Core\Include" -I"C:\Users\sandeep.mk\e2_studio\Working projects\GY-521\ra_gen" -I"C:\Users\sandeep.mk\e2_studio\Working projects\GY-521\ra_cfg\fsp_cfg" -I"C:\Users\sandeep.mk\e2_studio\Working projects\GY-521\ra_cfg\fsp_cfg\bsp" -I"C:\Users\sandeep.mk\e2_studio\Working projects\GY-521\src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


