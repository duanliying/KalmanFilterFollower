################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/ArPoseList.cpp \
../Source/Distance.cpp \
../Source/Filter.cpp \
../Source/PathLog.cpp \
../Source/RobotActions.cpp 

OBJS += \
./Source/ArPoseList.o \
./Source/Distance.o \
./Source/Filter.o \
./Source/PathLog.o \
./Source/RobotActions.o 

CPP_DEPS += \
./Source/ArPoseList.d \
./Source/Distance.d \
./Source/Filter.d \
./Source/PathLog.d \
./Source/RobotActions.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/Aria/include -I"/home/djfrmd/Development/CWorkspace/KalmanFilterFollower/Headers" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


