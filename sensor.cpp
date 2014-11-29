#include <cmath>
#include <iostream>
#include "Aria.h"
#include "Distance.hpp"
#include "Filter.hpp"
#include "PathLog.hpp"
#include "RobotActions.hpp"

#define IDEAL_DISTANCE 1500

using namespace std;

int main( int argc, char **argv ){
   // parse our args and make sure they were all accounted for
   ArSimpleConnector connector(&argc, argv);

   ArRobot robot;
   ArSick sick;
   double raw_d = 0, raw_a = 0;
   double filtered_d = 0, filtered_a = 0;

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
   robot.move(-1000);
   while(!robot.isMoveDone());
   robot.lock();
   robot.setVel(0);
   robot.unlock();

   // Start with a terrible estimation
   Filter kFilter(1, .00001, .1, 200, 45);

   ArUtil::sleep(5000);
   printf("Connected\n");

   // Open the sensor.dat file for recording
   ofstream output;
   output.open("../Data/sensor.dat", ios::out | ios::trunc);

   for( int i = 0; i < 400; i++ ){

      // Get the raw reading
      sick.lockDevice();
      raw_d = sick.currentReadingPolar(-90, 90, &raw_a);
      sick.unlockDevice();

      // Filter the reading
      filtered_d = raw_d;
      filtered_a = raw_a;
      kFilter.filter(&filtered_d, &filtered_a, 0, 0 );

      // Write the raw and filtered values to the file
      output << i << " " << raw_d << " " << raw_a << " " << filtered_d << " " << filtered_a << endl;

      ArUtil::sleep(100);

   }

   ArUtil::sleep(1000);
   output.close();

   Aria::exit(0);
   return 0;
}
