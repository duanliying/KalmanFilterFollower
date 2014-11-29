#!/bin/bash

# Add the following files
echo "\"\" 0 0" > ../Data/distance.dat 
cat ../Data/wander_dist.dat >> ../Data/distance.dat
cat ../Data/reactive_dist.dat >> ../Data/distance.dat
cat ../Data/kalman_dist.dat >> ../Data/distance.dat
echo "\"\" 2 4" >> ../Data/distance.dat 