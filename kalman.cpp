#include <cmath>
#include <iostream>
#include "Aria.h"
#include "Distance.hpp"
#include "Filter.hpp"
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
   ArPose p_o(0, -1000, 0);
   ArPose p_n;
   robot.moveTo(p_o);

   printf("Connected\n");
   ArUtil::sleep(1000);
   /* plot the path of the robot,
   * the position of the object robot measured from the sensors as well as
   * the position of the object robot predicted by the filter*/
   PathLog log("../Data/kalman.dat");
   PathLog p_pos("../Data/kalman_predict_position.dat");
   PathLog m_pos("../Data/kalman_measure_position.dat");
   Filter kFilter(1, .9, .1, 1000, 90);

   // Filter a few times before following
   for( int i = 0; i < 10; i++ ){
      sick.lockDevice();
      dist = sick.currentReadingPolar(-90, 90, &angle);
      sick.unlockDevice();
      kFilter.filter(&dist, &angle, 0, 0);
      ArUtil::sleep(100);
   }
   double pred_x, pred_y, meas_x, meas_y;
   double total_distance = 0;
   int iterations_wo_movement = 0;
   while( iterations_wo_movement < CONSECUTIVE_NON_MOTIONS ){

      sick.lockDevice();
      dist = sick.currentReadingPolar(-90, 90, &angle);
      sick.unlockDevice();

      // Get the amount our robot has moved
      p_n = robot.getPose();
      meas_x = p_n.getX() + dist * cos((p_n.getTh() + angle) * PI / 180);
      meas_y = p_n.getY() + dist * sin((p_n.getTh() + angle) * PI / 180);
      m_pos.write(meas_x, meas_y);
      kFilter.filter(&dist, &angle, getDistance(p_n, p_o), getAngle(p_n, p_o));
      pred_x = p_n.getX() + dist * cos((p_n.getTh() + angle) * PI / 180);
      pred_y = p_n.getY() + dist * sin((p_n.getTh() + angle) * PI / 180);
      p_pos.write(pred_x, pred_y);
      total_distance += getDistance(p_o, p_n);
      p_o = p_n;

      // If nothing is picked up, quit translating
      dist = calcDistWithBuffer(dist);
      trackRobot(&robot, dist, angle);
      ArUtil::sleep(500);
      log.write(robot.getPose());

      // Determine if the robot is done tracking
      isRobotTracking(&iterations_wo_movement, dist, angle);

   }

   ArUtil::sleep(1000);
   log.close();
   p_pos.close();
   m_pos.close();

   ofstream output;
   output.open("../Data/kalman_dist.dat", ios::out | ios::trunc);
   output << "Kalman 1.5 " << total_distance << endl;
   output.close();

   Aria::exit(0);
   return 0;
}
