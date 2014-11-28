/*
 * ArPoseList.hpp
 *
 *  Created on: Nov 24, 2014
 *      Author: djfrmd
 */

#ifndef SOURCE_ARPOSELIST_HPP_
#define SOURCE_ARPOSELIST_HPP_

#include <string>
#include "Aria.h"

using namespace std;

class ArPoseList {

      struct node {
            ArPose pose;
            node *next;
      };

   public:
      ArPoseList();
      ArPoseList( string file_name );
      ~ArPoseList();
      bool getPose( ArPose *retVal );
      void addPose( ArPose pose );

   private:
      node *head;

};

#endif /* SOURCE_ARPOSELIST_HPP_ */
