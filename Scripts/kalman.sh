#!/bin/bash

# Script starts the wandering program, then the reactive tracking program

# Start the wander program with robot 1
./wander.sh &

# Start the reactive tracking program with robot 2
../Kalman/./kalman -rrtp 8102