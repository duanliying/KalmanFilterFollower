/*
 * ArPoseList.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: djfrmd
 */
#include "ArPoseList.hpp"
#include <iostream>
using namespace std;

ArPoseList::ArPoseList(){

   head = NULL;

}

ArPoseList::~ArPoseList(){

   node *prev = NULL;
   node *cur = head;

   while( cur != NULL ){
      prev = cur;
      cur = cur->next;
      delete prev;
   }

}

bool ArPoseList::getPose( ArPose *retVal ){

   if( head == NULL ){
      retVal = NULL;
      return false;
   }

   node *tmp = head;
   *retVal = head->pose;

   head = head->next;

   delete tmp;

   return true;

}

void ArPoseList::addPose( ArPose pose ){

   // Create a new node to add to the list
   node *tmp = new node();
   tmp->pose = pose;
   tmp->next = NULL;

   // Empty List
   if( head == NULL ){
      head = tmp;
      return;
   }

   // Non-Empty List
   node *cur = head;

   // Find end of list
   while( cur->next != NULL ){
      cur = cur->next;
   }

   // Add to list
   cur->next = tmp;

}

