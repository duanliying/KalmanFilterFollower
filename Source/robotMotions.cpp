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

   robot->lock();
   robot->setHeading(dir);
   robot->unlock();

   translate(robot, dist);

}

void translate( ArRobot *robot, double dist ){

   robot->lock();
   robot->move(dist);
   robot->unlock();

}

void trackRobot( ArRobot *robot, ArPose pose ){

   trackRobot(robot, robot->findDistanceTo(pose), robot->findAngleTo(pose));

}

void trackRobot( ArRobot *robot, double dist, double dir ){

   robot->lock();
   robot->setDeltaHeading(dir);
   robot->unlock();

   translate(robot, dist);

}
