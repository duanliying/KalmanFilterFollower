################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/TrackedObject/PathLog.cpp 

OBJS += \
./Source/TrackedObject/PathLog.o 

CPP_DEPS += \
./Source/TrackedObject/PathLog.d 


# Each subdirectory must supply rules for building sources it contributes
Source/TrackedObject/%.o: ../Source/TrackedObject/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/Aria/include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


