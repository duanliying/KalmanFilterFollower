/*
 * Filter.hpp
 *
 *  Created on: Nov 26, 2014
 *      Author: djfrmd
 */

#ifndef FILTER_HPP_
#define FILTER_HPP_

using namespace std;

class Filter{

   public:
      Filter(double p, double q, double r, double d, double th);
      void filter(double* in_d, double* in_th, double ctl_d, double ctl_th);

   protected:
      double P[2][2];
      double Q[2][2];
      double R[2][2];
      double X[2];
      double I[2][2];
      double K[2][2];

};

#endif /* FILTER_HPP_ */
