/**
 * File: pairing.cpp
 * Author: Michael McCormick
 * Date: 03-04-2018
 * Desc: Contains functions related to pairing the two MicroBits
 * Copyright: University of West of England 2018
 */

 #include "pairing.h"

 PairingClass::PairingClass() {
   //Constructor
 }

 int PairingClass::randomInt(int min, int max, uint64_t sysTime) {
   srand(sysTime); // Set random seed
   int returnVar = rand() % max + min; // Generate random number
   return returnVar;
 }
