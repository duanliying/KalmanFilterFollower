/*
 * trackingobject.cpp
 *
 *  Created on: Nov 23, 2014
 *     Authors: Chris Arnold & Dallas Fletchall
 */
#include <iostream>
#include <sstream>
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
      istringstream i(line);
      double x, y, th;
      i >> x >> y >> th;
      ArPose pose(x,y,th);
      poses.addPose(pose);

   }
   input.close();


   Aria::init();

   ArArgumentParser parser(&argc, argv);

   parser.loadDefaultArguments();

   ArRobot robot;
   ArRobotConnector robotConnector(&parser, &robot);

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

   if( !Aria::parseArgs() || !parser.checkHelpAndWarnUnparsed() ){
      Aria::logOptions();
      Aria::exit(1);
      return 1;
   }

   ArKeyHandler keyHandler;
   Aria::setKeyHandler(&keyHandler);
   robot.attachKeyHandler(&keyHandler);
   printf("You may press escape to exit\n");

   robot.runAsync(true);

   ArUtil::sleep(500);

   robot.lock();

   robot.setAbsoluteMaxTransVel(850);
   robot.setAbsoluteMaxRotVel(50);
   robot.comInt(ArCommands::ENABLE, 1);

   robot.unlock();

   PathLog log("../Data/comparison.dat");


   ArPose pose;
   while(poses.getPose(&pose)){

      moveRobot(&robot, pose);
      log.write(robot.getPose());
      ArUtil::sleep(500);

   }

   Aria::exit(0);
   return 0;

}
