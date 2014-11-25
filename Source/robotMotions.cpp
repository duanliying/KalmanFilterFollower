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

   cout << robot->findAngleTo(pose) << ":" << robot->findDistanceTo(pose) << endl;
   moveRobot(robot, robot->findDistanceTo(pose), robot->findAngleTo(pose));

}

void moveRobot( ArRobot *robot, double dist, double dir ){

   robot->lock();
   robot->setHeading(dir);
   robot->move(dist);
   robot->unlock();

}

