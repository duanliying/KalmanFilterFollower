/*
 * Filter2.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: djfrmd
 */
#include "Filter2.hpp"

Filter2::Filter2(double P, double Q, double R, double X){

   k = 0;
   x = X;
   p = P;
   q = Q;
   r = R;

}


double Filter2::filter(double measurement){

   p = p + q;
   k = p / (p + r);
   x = x + k * (measurement - x);
   p = (1 - k) * p;

   return x;

}



