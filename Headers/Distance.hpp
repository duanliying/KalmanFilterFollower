/*
 * Distance.hpp
 *
 *  Created on: Nov 28, 2014
 *      Author: djfrmd
 */

#ifndef DISTANCE_HPP_
#define DISTANCE_HPP_

#include <string>
#include "ArPoseList.hpp"

using namespace std;

double getAngle( ArPose new_pose, ArPose old_pose );

double calcDistWithBuffer( double dist );

double getDistance( ArPose p1, ArPose p2 );

void isRobotTracking( int *count, double dist, double angle );

#endif /* DISTANCE_HPP_ */
