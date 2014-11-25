/*
 * robotMotions.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: djfrmd
 */
#include <cmath>
#include <iostream>
#include "robotMotions.hpp"

using namespace std;

void moveRobot( ArRobot *robot, ArPose pose ){

   moveRobot(robot, robot->findDistanceTo(pose), robot->findAngleTo(pose));

}

void moveRobot( ArRobot *robot, double dist, double dir ){

   turn(robot, dir);
   translate(robot, dist);

}

void turn( ArRobot *robot, double angle ){

   robot->lock();
   robot->setHeading(angle);
   robot->unlock();

}

void translate( ArRobot *robot, double dist ){

   robot->lock();
   robot->move(dist);
   robot->unlock();

}
