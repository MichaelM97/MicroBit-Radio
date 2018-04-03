#ifndef PAIRING_H
#define PAIRING_H

#include <stdlib.h>

using namespace std;

class PairingClass {

public:
  //Class Constructor
  PairingClass();
  //Generates a random number between min - max, using sysTime as a random seed
  int randomInt(int min, int max, uint64_t sysTime);

};

#endif
