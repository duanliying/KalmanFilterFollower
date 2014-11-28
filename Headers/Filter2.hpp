/*
 * Filter2.hpp
 *
 *  Created on: Nov 26, 2014
 *      Author: djfrmd
 */

#ifndef FILTER2_HPP_
#define FILTER2_HPP_

class Filter2{

   public:
      Filter2(double P, double Q, double R, double X);
      double filter(double measurement);
      double x, p, q, k, r;

};



#endif /* FILTER2_HPP_ */
