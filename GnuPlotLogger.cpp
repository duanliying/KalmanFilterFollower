/*
 * Logger.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: djfrmd
 */
#include "GnuPlotLogger.hpp"

GnuPlotLogger::GnuPlotLogger( string filename ){
   output.open(filename.c_str(), ios::out | ios::trunc);
}

GnuPlotLogger::~GnuPlotLogger(){
   if( output.is_open() ){
      output.close();
   }
}

void GnuPlotLogger::write( double x, double y ){

   if( output.is_open() ){
      output << x << " " << y << endl;
   }else{
      cout << "Unable to log position, file not open" << endl;
   }

}

void GnuPlotLogger::write( ArPose pose ){
   write(pose.getX(), pose.getY());
}

