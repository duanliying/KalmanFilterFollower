/*
 * Logger.hpp
 *
 *  Created on: Nov 24, 2014
 *      Author: djfrmd
 */

#ifndef GNUPLOTLOGGER_HPP_
#define GNUPLOTLOGGER_HPP_

#include <iostream>
#include <fstream>
#include "Aria.h"

using namespace std;

class GnuPlotLogger {

   public:
      GnuPlotLogger( string filename );
      ~GnuPlotLogger();

      void write( double x, double y );
      void write( ArPose pose );

   private:
      ofstream output;

};

#endif /* LOGGER_HPP_ */
