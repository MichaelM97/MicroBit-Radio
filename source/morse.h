#ifndef MORSE_H
#define MORSE_H

#include <map>
#include <string>

//ENCRYPTION KEY
#define ENCRYPTION_KEY 3

using namespace std;

class MorseClass {

public:
  //Class Constructor
  MorseClass();
  //Gets letter associated with passed morse code
  char getLetter(string morseCode);
  //Gets morse code associated with passed letter
  string getMorse(char letter);
  //Encrypts passed letter using Caeser cipher method + the set Key
  char encrypt(char letter);
  //Decrpyts passed letter using Caeser cipher method + the set Key
  char decrypt(char letter);

private:
  //Used for mapping morsecode to letters
  map<string, char> morseMap = {
     {".-", 'A'},
     {"-...", 'B'},
     {"-.-.", 'C'},
     {"-..", 'D'},
     {".", 'E'},
     {"..-.", 'F'},
     {"--.", 'G'},
     {"....", 'H'},
     {"..", 'I'},
     {".---", 'J'},
     {"-.-", 'K'},
     {".-..", 'L'},
     {"--", 'M'},
     {"-.", 'N'},
     {"---", 'O'},
     {".--.", 'P'},
     {"--.-", 'Q'},
     {".-.", 'R'},
     {"...", 'S'},
     {"-", 'T'},
     {"..-", 'U'},
     {"...-", 'V'},
     {".--", 'W'},
     {"-..-", 'X'},
     {"-.--", 'Y'},
     {"--..", 'Z'},
     {".----", '1'},
     {"..---", '2'},
     {"...--", '3'},
     {"....-", '4'},
     {"-....", '6'},
     {".....", '5'},
     {"--...", '7'},
     {"---..", '8'},
     {"----.", '9'},
     {"-----", '0'}
  };

  //Iterator used to find elements in map
  map<string, char>::iterator mapItr;

};

#endif
