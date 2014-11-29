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
./pause.sh
./kalman.sh
gnuplot -p ../Misc/kalman.gpt

# Total Distance Plot
./distance_calc.sh
gnuplot -p ../Misc/distance.gpt


