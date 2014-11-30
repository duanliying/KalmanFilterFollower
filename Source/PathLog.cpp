/*
 * PathLog.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: djfrmd
 */
#include "PathLog.hpp"

PathLog::PathLog( string filename ){

   output.open(filename.c_str(), ios::out | ios::trunc);
   counter = 0;

}

PathLog::~PathLog(){

   close();

}

void PathLog::write( double x, double y, double theta ){

   if( output.is_open() ){
      output << x << " " << y << " " << theta << endl;
   }else{
      cout << "Unable to log position, file not open" << endl;
   }

}

void PathLog::write( ArPose pose ){

   write(pose.getX(), pose.getY(), pose.getTh());

}

void PathLog::write( double difference ){
    if ( output.is_open() ){
	output << counter++ << " " << difference << endl;
    } else{
	cout << "Unable to log difference, file not open" << endl;
    }
}

void PathLog::write( double x, double y ){
    if ( output.is_open() ){
	output << x << " " << y << endl;
    } else{
	cout << "Unable to log difference, file not open" << endl;
    }
}

void PathLog::close(){

   if( output.is_open() ){
      output.close();
   }

}

