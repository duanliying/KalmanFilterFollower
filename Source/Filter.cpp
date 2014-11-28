/*
 * Filter.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: djfrmd
 */
#include "Filter.hpp"
#include <cmath>
#include <iostream>

using namespace std;

Filter::Filter(double p, double q, double r, double d, double th){

   // A = I
   // B = I
   // H = I

   // Setup the P matrix
   P[0][0] = p; P[0][1] = 0;
   P[1][0] = 0; P[1][1] = p;

   // Setup the Q matrix
   Q[0][0] = q; Q[0][1] = 0;
   Q[1][0] = 0; Q[1][1] = q;

   // Setup the R matrix
   R[0][0] = r; R[0][1] = 0;
   R[1][0] = 0; R[1][1] = r;

   // Setup the K matrix
   K[0][0] = 0; K[0][1] = 0;
   K[1][0] = 0; K[1][1] = 0;

   // Setup the X vector
   X[0] = d;
   X[1] = th;

}

void Filter::filter( double* in_d, double* in_th, double ctl_d, double ctl_th ){

   // State Prediction
   double x_predicted[2];
   x_predicted[0] = X[0] + ctl_d;
   x_predicted[1] = X[1] + ctl_th;

   // Covariance Prediction
   double p_predicted[2][2];
   p_predicted[0][0] = P[0][0] + Q[0][0]; p_predicted[0][1] = P[0][1] + Q[0][1];
   p_predicted[1][0] = P[1][0] + Q[1][0]; p_predicted[1][1] = P[1][1] + Q[1][1];

   // Innovation
   double y_hat[2];
   y_hat[0] = *in_d - x_predicted[0];
   y_hat[1] = *in_th - x_predicted[1];

   // Innovation Covariance
   double S[2][2];
   S[0][0] = p_predicted[0][0] + R[0][0]; S[0][1] = p_predicted[0][1] + R[0][1];
   S[1][0] = p_predicted[1][0] + R[1][0]; S[1][1] = p_predicted[1][1] + R[1][1];

   // Kalman Gain
   double c = 1 / (S[0][0]*S[1][1] - S[0][1]*S[1][0]);
   double S_inv[2][2];
   S_inv[0][0] =  c*S[1][1]; S_inv[0][1] = -c*S[0][1];
   S_inv[1][0] = -c*S[1][0]; S_inv[1][1] =  c*S[0][0];
   K[0][0] = p_predicted[0][0]*S_inv[0][0] + p_predicted[0][1]*S_inv[1][0];
   K[0][1] = p_predicted[0][0]*S_inv[0][1] + p_predicted[0][1]*S_inv[1][1];
   K[1][0] = p_predicted[1][0]*S_inv[0][0] + p_predicted[1][1]*S_inv[1][0];
   K[1][1] = p_predicted[1][0]*S_inv[0][1] + p_predicted[1][1]*S_inv[1][1];

   // State Update
   double ky_hat[2];
   ky_hat[0] = K[0][0]*y_hat[0] + K[0][1]*y_hat[1];
   ky_hat[1] = K[1][0]*y_hat[0] + K[1][1]*y_hat[1];
   X[0] = x_predicted[0] + ky_hat[0];
   X[1] = x_predicted[1] + ky_hat[1];

   // Covariance Update
   P[0][0] = (1 - K[0][0])*p_predicted[0][0] + K[0][1]*p_predicted[1][0];
   P[0][1] = (1 - K[0][0])*p_predicted[0][1] + K[0][1]*p_predicted[1][1];
   P[1][0] = K[1][0]*p_predicted[0][0] + (1 - K[1][1])*p_predicted[1][0];
   P[1][1] = K[1][0]*p_predicted[0][1] + (1 - K[1][1])*p_predicted[1][1];

   // Return Values
   *in_d  = X[0];
   *in_th = X[1];

}
