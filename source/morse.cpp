/**
 * File: morse.cpp
 * Author: Michael McCormick
 * Date: 09-03-2018
 * Desc: Contains functions related to manipulating morse code data
 * Copyright: University of West of England 2018
 */

#include "MicroBit.h"
#include "morse.h"

MorseClass::MorseClass() {
  //Constructor
}

char MorseClass::getLetter(string morseCode) {
  char returnVar = '?';
  mapItr = morseMap.find(morseCode);
  if (mapItr == morseMap.end()) {
      //If invalid input
  } else {
      returnVar = mapItr->second;
  }
  return returnVar;
}

string MorseClass::getMorse(char letter) {
  string returnVar = "?";
  for (mapItr = morseMap.begin(); mapItr != morseMap.end(); ++mapItr) {
    if (letter == mapItr->second) {
      returnVar = mapItr->first;
      break;
    }
  }
  return returnVar;
}

char MorseClass::encrypt(char letter) {
  char returnVar = '?';
  //Loop through map to find letter position
  for (mapItr = morseMap.begin(); mapItr != morseMap.end(); ++mapItr) {
    if (letter == mapItr->second) {
        //Shift the letters position to the right by 3
        switch (letter) {
          case '8':
            returnVar = 'A';
            break;
          case '9':
            returnVar = 'B';
            break;
          case '0':
            returnVar = 'C';
            break;
          default:
            advance(mapItr, ENCRYPTION_KEY);
            returnVar = mapItr->second;
        }
      break;
    }
  }
  return returnVar;
}

char MorseClass::decrypt(char letter) {
  char returnVar = '?';
  //Loop through map to find letter position
  for (mapItr = morseMap.begin(); mapItr != morseMap.end(); ++mapItr) {
    if (letter == mapItr->second) {
      //Shift the letters position to the left by 3
      switch (letter) {
        case 'A':
          returnVar = '8';
          break;
        case 'B':
          returnVar = '9';
          break;
        case 'C':
          returnVar = '0';
          break;
        default:
          mapItr = prev(mapItr, 3);
          returnVar = mapItr->second;
      }
    break;
    }
  }
  return returnVar;
}
