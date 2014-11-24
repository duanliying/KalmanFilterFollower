/*
 * PathLog.hpp
 *
 *  Created on: Nov 24, 2014
 *      Author: djfrmd
 */
#include <iostream>
#include <fstream>
#include "Aria.h"

using namespace std;

class PathLog{
   public:
      PathLog(string filename);
      ~PathLog();

      void write(double x, double y, double theta);
      void write(ArPose pose);

   private:
      ofstream output;

};

