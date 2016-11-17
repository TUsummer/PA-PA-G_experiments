################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mapxy/mapxy.cpp 

OBJS += \
./src/mapxy/mapxy.o 

CPP_DEPS += \
./src/mapxy/mapxy.d 


# Each subdirectory must supply rules for building sources it contributes
src/mapxy/%.o: ../src/mapxy/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


