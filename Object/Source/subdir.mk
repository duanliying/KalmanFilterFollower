################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/ArPoseList.cpp \
../Source/Filter.cpp \
../Source/PathLog.cpp \
../Source/robotMotions.cpp 

OBJS += \
./Source/ArPoseList.o \
./Source/Filter.o \
./Source/PathLog.o \
./Source/robotMotions.o 

CPP_DEPS += \
./Source/ArPoseList.d \
./Source/Filter.d \
./Source/PathLog.d \
./Source/robotMotions.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/Aria/include -I/usr/local/lib -I"/home/djfrmd/Development/CWorkspace/KalmanFilterFollower/Headers" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


