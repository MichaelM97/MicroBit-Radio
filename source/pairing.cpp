/**
 * File: pairing.cpp
 * Author: Michael McCormick
 * Date: 06-04-2018
 * Desc: Contains functions related to pairing the MicroBits
 * Copyright: University of West of England 2018
 */

#include "MicroBit.h"
#include "pairing.h"

PairingClass::PairingClass() {
  //Constructor
}

int PairingClass::randomInt(int min, int max, uint64_t sysTime) {
 srand(sysTime); //Use current system up time as random seed
 int returnVar = rand() % max + min; //Generate random number
 return returnVar;
}

ManagedString PairingClass::dataString(int newGroup, int newFrequency, const char* delimiter) {
  //Convert variables to correct types
  ManagedString newGroupStr = newGroup;
  ManagedString newFrequencyStr = newFrequency;
  ManagedString delimiterStr = delimiter;
  //Concatenate variables
  ManagedString returnVar = newGroupStr + delimiterStr + newFrequencyStr + delimiterStr;
  return returnVar;
}
