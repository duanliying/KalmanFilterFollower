/*
 * robotMotions.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: djfrmd
 */
#include <cmath>
#include <iostream>
#include "RobotActions.hpp"

#define DISTANCE_STOP_BUFFER 10
#define ANGLE_STOP_BUFFER 5
#define CONSECUTIVE_NON_MOTIONS 5

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

void isRobotTracking( int *count, double dist, double angle ){

   if( abs(dist) > DISTANCE_STOP_BUFFER || abs(angle) > ANGLE_STOP_BUFFER){
      *count = *count + 1;
   }else{
      *count = CONSECUTIVE_NON_MOTIONS;
   }

}
