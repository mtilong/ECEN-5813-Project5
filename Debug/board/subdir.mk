################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/pin_mux.c 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/pin_mux.o 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DDEBUG -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DFRDM_KL25Z -DFREEDOM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -I"/Users/mtilong/Desktop/MCUXpressoIDE_11.1.0/workspace/Project5turnin/board" -I"/Users/mtilong/Desktop/MCUXpressoIDE_11.1.0/workspace/Project5turnin/source" -I"/Users/mtilong/Desktop/MCUXpressoIDE_11.1.0/workspace/Project5turnin" -I"/Users/mtilong/Desktop/MCUXpressoIDE_11.1.0/workspace/Project5turnin/drivers" -I"/Users/mtilong/Desktop/MCUXpressoIDE_11.1.0/workspace/Project5turnin/CMSIS" -I"/Users/mtilong/Desktop/MCUXpressoIDE_11.1.0/workspace/Project5turnin/utilities" -I"/Users/mtilong/Desktop/MCUXpressoIDE_11.1.0/workspace/Project5turnin/startup" -O0 -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


