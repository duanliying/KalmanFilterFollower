#!/bin/bash

# Script utilizes scripts from Script/ folder in the order for the presentation

# Start the MobileSim program
./msim.sh &

# Wait for user input before starting to record path of object
echo "Press Enter to Continue:"
read
./object.sh

# Wander Program
echo "Press Enter to Continue:"
read
./wander.sh
# Plot the graph of the object and wander to show similarity
gnuplot -p ../Misc/path_duplication.gpt

# Reactive Program
#echo "Press Enter to Continue:"
#read
#./wander.sh
# TODO: Plot the graph of the wandering and reactive tracking robots

# Kalman Program
# TODO: Create Kalman program and script
# TODO: Plot the graph of the wandering and kalman tracking robots

# TODO: Plot all graphs


