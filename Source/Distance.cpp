/*
 * Distance.cpp
 *
 *  Created on: Nov 28, 2014
 *      Author: djfrmd
 */
#include <cmath>
#include "Aria.h"
#include "Distance.hpp"
#include "RobotActions.hpp"
#include <iostream>

#define IDEAL_DISTANCE 1500
#define MAX_SENSOR_DIST 32000

using namespace std;

double calcDistWithBuffer( double dist ){
   return (dist > MAX_SENSOR_DIST - 1000) ? 0 : dist - IDEAL_DISTANCE;
}

double getDistance( ArPose p1, ArPose p2 ){

   double dx = p1.getX() - p2.getX();
   double dy = p1.getY() - p2.getY();
   return sqrt(dx * dx + dy * dy);

}

double getAngle( ArPose new_pose, ArPose old_pose ){
   return new_pose.getTh() - old_pose.getTh();
}
