/*
 * robotMotions.hpp
 *
 *  Created on: Nov 24, 2014
 *      Author: djfrmd
 */

#ifndef SOURCE_ROBOTMOTIONS_HPP_
#define SOURCE_ROBOTMOTIONS_HPP_

#include "Aria.h"

void moveRobot( ArRobot *robot, double dist, double dir );
void moveRobot( ArRobot *robot, ArPose pose );

void turn( ArRobot *robot, double angle );
void translate( ArRobot *robot, double dist );

#endif /* SOURCE_ROBOTMOTIONS_HPP_ */
