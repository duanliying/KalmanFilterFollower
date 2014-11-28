/*
 * robotMotions.hpp
 *
 *  Created on: Nov 24, 2014
 *      Author: djfrmd
 */

#ifndef SOURCE_ROBOTACTIONS_HPP_
#define SOURCE_ROBOTACTIONS_HPP_

#include "Aria.h"

#define CONSECUTIVE_NON_MOTIONS 5

void moveRobot( ArRobot *robot, double dist, double dir );
void moveRobot( ArRobot *robot, ArPose pose );

void trackRobot( ArRobot *robot, double dist, double dir );
void trackRobot( ArRobot *robot, ArPose pose );

void translate( ArRobot *robot, double dist );

void isRobotTracking( int *count, double dist, double angle );

#endif /* SOURCE_ROBOTACTIONS_HPP_ */
