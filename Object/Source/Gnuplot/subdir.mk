################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Gnuplot/GnuPlotLogger.cpp 

OBJS += \
./Source/Gnuplot/GnuPlotLogger.o 

CPP_DEPS += \
./Source/Gnuplot/GnuPlotLogger.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Gnuplot/%.o: ../Source/Gnuplot/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/Aria/include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


