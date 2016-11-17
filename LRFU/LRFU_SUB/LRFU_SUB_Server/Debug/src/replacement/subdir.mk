################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/replacement/replacement.cpp 

OBJS += \
./src/replacement/replacement.o 

CPP_DEPS += \
./src/replacement/replacement.d 


# Each subdirectory must supply rules for building sources it contributes
src/replacement/%.o: ../src/replacement/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


