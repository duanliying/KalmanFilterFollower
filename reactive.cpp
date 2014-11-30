#include <iostream>
#include <cmath>
#include "Aria.h"
#include "Distance.hpp"
#include "PathLog.hpp"
#include "RobotActions.hpp"

#define IDEAL_DISTANCE 1500
#define PI 3.14159265

using namespace std;

int main( int argc, char **argv ){
   // parse our args and make sure they were all accounted for
   ArSimpleConnector connector(&argc, argv);

   ArRobot robot;
   ArSick sick;
   double dist, angle = 0;

   // Allow for esc to release robot
   ArKeyHandler keyHandler;
   Aria::setKeyHandler(&keyHandler);
   robot.attachKeyHandler(&keyHandler);
   printf("You may press escape to exit\n");

   if( !connector.parseArgs() || argc > 1 ){
      connector.logOptions();
      exit(1);
   }

   // add the laser to the robot
   robot.addRangeDevice(&sick);

   // try to connect, if we fail exit
   if( !connector.connectRobot(&robot) ){
      printf("Could not connect to robot... exiting\n");
      Aria::shutdown();
      return 1;
   }

   // start the robot running, true so that if we lose connection the run stops
   robot.runAsync(true);

   // now set up the laser
   connector.setupLaser(&sick);

   sick.runAsync();

   if( !sick.blockingConnect() ){
      printf("Could not connect to SICK laser... exiting\n");
      Aria::shutdown();
      return 1;
   }

   robot.comInt(ArCommands::ENABLE, 1);
   ArPose pose(0, -1000, 0);
   robot.moveTo(pose);
   ArPose prev_pose = robot.getPose();
   double total_distance = 0;

   printf("Connected\n");
   ArUtil::sleep(1000);

   PathLog log("../Data/reactive.dat");
   int iterations_wo_movement = 0;
   while( iterations_wo_movement < CONSECUTIVE_NON_MOTIONS ){

      // Get updated measurement
      sick.lockDevice();
      dist = sick.currentReadingPolar(-90, 90, &angle);
      sick.unlockDevice();

      dist = (dist > 30000) ? 0 : dist - IDEAL_DISTANCE;
      trackRobot(&robot, dist, angle);
      ArUtil::sleep(500);
      pose = robot.getPose();
      log.write(pose);
      total_distance += getDistance(prev_pose, pose);
      prev_pose = pose;

      // Determine if the robot is done tracking
      isRobotTracking(&iterations_wo_movement, dist, angle);

   }

   ArUtil::sleep(1000);
   log.close();

   ofstream output;
   output.open("../Data/reactive_dist.dat", ios::out | ios::trunc);
   output << "Reactive 1 " << total_distance << endl;
   output.close();

   Aria::exit(0);
   return 0;
}
