#!/bin/bash

# Script utilizes scripts from Script/ folder in the order for the presentation

# Start the MobileSim program
./msim.sh &
sleep 2

# Wait for user input before starting to record path of object
./pause.sh
./object.sh

# Wander Program
./pause.sh
./wander.sh
gnuplot -p ../Misc/path_duplication.gpt

# Reactive Program
./pause.sh
./reactive.sh
gnuplot -p ../Misc/reactive.gpt

# Kalman Program
clear
# TODO: Create Kalman program and script
# TODO: Plot the graph of the wandering and kalman tracking robots

# TODO: Plot all graphs


