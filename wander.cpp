/*
 * trackingobject.cpp
 *
 *  Created on: Nov 23, 2014
 *     Authors: Chris Arnold & Dallas Fletchall
 */
#include <iostream>
#include <fstream>
#include <string>
#include "Aria.h"
#include "PathLog.hpp"
#include "robotMotions.hpp"
#include "ArPoseList.hpp"

using namespace std;

int main( int argc, char** argv ){

   // Read all poses from the file
   ArPoseList poses;
   ifstream input("../Data/object.dat", ifstream::in);
   if(!input.is_open()){
      cout << "Error opening file" << endl;
      return 1;
   }

   string line;
   while(getline(input, line)){
      cout << line << endl;
   }
   input.close();

   return 0;

   Aria::init();

   ArArgumentParser parser(&argc, argv);

   parser.loadDefaultArguments();

   ArRobot robot;

   ArRobotConnector robotConnector(&parser, &robot);

   ArAnalogGyro gyro(&robot);

   if( !robotConnector.connectRobot() ){

      if( !parser.checkHelpAndWarnUnparsed() ){
         ArLog::log(ArLog::Terse, "Could not connect to robot");
      }else{
         ArLog::log(ArLog::Terse, "Error, could not connect to robot.");
         Aria::logOptions();
         Aria::exit(1);
      }
   }

   if( !robot.isConnected() ){
      ArLog::log(ArLog::Terse, "Internal error: connection failed");
   }

   ArLaserConnector laserConnector(&parser, &robot, &robotConnector);

   ArCompassConnector compassConnector(&parser);

   if( !Aria::parseArgs() || !parser.checkHelpAndWarnUnparsed() ){
      Aria::logOptions();
      Aria::exit(1);
      return 1;
   }

   ArSonarDevice sonarDev;

   ArKeyHandler keyHandler;
   Aria::setKeyHandler(&keyHandler);

   robot.attachKeyHandler(&keyHandler);
   printf("You may press escape to exit\n");

   robot.addRangeDevice(&sonarDev);

   robot.runAsync(true);

   if( !laserConnector.connectLasers(false, false, true) ){
      printf("Could not connect to lasers... exiting\n");
      Aria::exit(2);
   }

   ArTCM2 *compass = compassConnector.create(&robot);
   if( compass && !compass->blockingConnect() ){
      compass = NULL;
   }

   ArUtil::sleep(1000);

   robot.lock();

   if( robot.getOrigRobotConfig()->getHasGripper() ){
      new ArModeGripper(&robot, "gripper", 'g', 'G');
   }else{
      ArLog::log(ArLog::Normal, "Robot does not have a gripper.");
   }
   ArModeActs actsMode(&robot, "acts", 'a', 'A');
   ArModeTCM2 tcm2(&robot, "tcm2", 'm', 'M', compass);
   ArModeIO io(&robot, "io", 'i', 'I');
   ArModeConfig cfg(&robot, "report robot config", 'o', 'O');
   ArModeCommand command(&robot, "command", 'd', 'D');
   ArModeCamera camera(&robot, "camera", 'c', 'C');
   ArModePosition position(&robot, "position", 'p', 'P', &gyro);
   ArModeSonar sonar(&robot, "sonar", 's', 'S');
   ArModeBumps bumps(&robot, "bumps", 'b', 'B');
   ArModeLaser laser(&robot, "laser", 'l', 'L');
   ArModeWander wander(&robot, "wander", 'w', 'W');
   ArModeUnguardedTeleop unguardedTeleop(&robot, "unguarded teleop", 'u', 'U');
   ArModeTeleop teleop(&robot, "teleop", 't', 'T');

   teleop.activate();

   robot.comInt(ArCommands::ENABLE, 1);

   robot.unlock();

   robot.waitForRunExit();

   Aria::exit(0);
   return 0;

}
