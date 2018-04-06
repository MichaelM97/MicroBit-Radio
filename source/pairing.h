#ifndef PAIRING_H
#define PAIRING_H

#include <string>

using namespace std;

class PairingClass {

public:
  //Class Constructor
  PairingClass();
  //Generates a random number between min - max, using the time as a seed
  int randomInt(int min, int max, uint64_t sysTime);
  //Returns the ManagedString containing the pairing data to be sent
  ManagedString dataString(int newGroup, int newFrequency, const char* delimiter);

};

#endif
