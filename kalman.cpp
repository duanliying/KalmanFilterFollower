#include "Aria.h"
#include <iostream>
#include <cmath>
#include "robotMotions.hpp"
#include "PathLog.hpp"
#include "Filter2.hpp"

#define IDEAL_DISTANCE 1500

using namespace std;

void printDistAng( double d, double a );

int main( int argc, char **argv ){
   // parse our args and make sure they were all accounted for
   ArSimpleConnector connector(&argc, argv);

   ArRobot robot;
   ArSick sick;
   double dist, angle = 0;
   std::list<ArPoseWithTime *>::iterator it;

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

   printf("Connected\n");
   ArUtil::sleep(1000);

   PathLog log("../Data/reactive.dat");
   Filter2 kf_x(.04, 1.38, .06, 32, 0);
   Filter2 kf_y(.04, 1.38, .06, 32, 1000);
   double x_p;
   double y_p;
   double d_p;
   double a_p;

   int stop = 10;

   while( stop > 0 ){

      sick.lockDevice();
      dist = sick.currentReadingPolar(-90, 90, &angle);
      sick.unlockDevice();

      x_p = kf_x.filter(dist*cos(angle));
      y_p = kf_y.filter(dist*sin(angle));
      d_p = sqrt(x_p * x_p + y_p * y_p);
      a_p = atan2(y_p, x_p);

      // If nothing is picked up, quit translating
      dist = (dist > 30000) ? 0 : dist - IDEAL_DISTANCE;
      trackRobot(&robot, d_p, a_p);
      log.write(robot.getPose());

      // Determine if the robot is done tracking
      if( abs(dist) < 5 && abs(angle) < 5 ){
         stop--;
      }else{
         stop = 5;
      }
      ArUtil::sleep(500);

   }

   Aria::exit(0);
   return 0;
}

void printDistAng( double d, double a ){

   cout << "D: " << d << " A: " << a << endl;
}
