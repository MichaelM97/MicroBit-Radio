/**
 * File: main.cpp
 * Author: Michael McCormick
 * Date: 06-04-2018
 * Desc: Basic pairing & transmission protocol for morse code sent across 2
 * microbits connected via the radio. Implements a basic encryption cypher.
 * Copyright: University of West of England 2018
 */
#include "MicroBit.h"
#include "morse.h"
#include "pairing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>

/* Global constants */
//Timings used for distinguishing between dot/dash transmissions
#define DOT_TIME 250
#define DASH_TIME 500
//Data that is sent/recieved to confirm pairing
#define CONFIRM_MESSAGE "confirm"
//Character used for splitting pairing data string
#define PAIR_DELIMITER ","

using namespace std;

/* Function Prototypes */
//Handles all potential data incoming from the radio
void onData(MicroBitEvent e);

/* Global variables */
//Flags used to track pairing status
bool pairingStarted, paired, confirmWait, confirmed;
//Variables used for pairing
int newGroup, newFrequency;
//Used to store incoming morse code
string incomingMorse;
//Flag used to indicate morse data has been recieved
bool morseRecieved;

//Used to access microbit
MicroBit uBit;

//Images used for displaying dot/dash
MicroBitImage DOT_IMAGE("0,0,0,0,0\n0,0,0,0,0\n0,0,255,0,0\n0,0,0,0,0\n0,0,0,0,0\n");
MicroBitImage DASH_IMAGE("0,0,0,0,0\n0,0,0,0,0\n0,255,255,255,0\n0,0,0,0,0\n0,0,0,0,0\n");

//Button events
MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);
MicroBitButton buttonB(MICROBIT_PIN_BUTTON_B, MICROBIT_ID_BUTTON_B);

int main()
{
    //Initialise the micro:bit runtime.
    uBit.init();
    uBit.radio.enable();

    //Create instance of classes
    MorseClass* morse = new MorseClass();
    PairingClass* pairing = new PairingClass();

    //Variables used for morse transmissions
    bool buttonPressed = false, morseSent = false;
    uint64_t buttonTime = 0, buttonDuration = 0, buttonWaiting = 0;
    string transmissionBuffer;
    char letter;

    //Set flags
    paired = false;
    pairingStarted = false;
    confirmWait = false;
    confirmed = false;
    morseRecieved = false;

    //Handle pairing procedure
    while (1) {
      uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);
      //Wait for button input
      if (buttonB.isPressed()) {
        pairingStarted = true;
      }

      /** HANDLE USER CONFIRM **/
      uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);
      uBit.sleep(100);
      if (confirmed == true) {
        //Send confirm message and update pairing status
        uBit.radio.datagram.send(CONFIRM_MESSAGE);
        paired = true;
        pairingStarted = false;
      }

      /** HANDLE START PAIRING **/
      else if (pairingStarted == true) {
        uBit.display.scroll("PAIRING");
        //Get new random variables
        newGroup = pairing->randomInt(0, 255, uBit.systemTime());
        uBit.sleep(100);
        newFrequency = pairing->randomInt(0, 100, uBit.systemTime());
        //Send variables across radio, merge using global delimiter
        ManagedString randomNums = pairing->dataString(newGroup, newFrequency, PAIR_DELIMITER);
        uBit.radio.datagram.send(randomNums);
        uBit.sleep(100);
        //Wait for confirmation
        uint64_t startedWaiting = uBit.systemTime();
        confirmWait = true;
        while (1) {
          uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);
          uBit.sleep(50);
          if (paired == true) {
            //Will continue to MorseCode handling
            confirmWait = false;
            pairingStarted = false;
            break;
          } else if ((uBit.systemTime() - startedWaiting) > 10000) {
            uBit.display.scroll("X"); //Will go back to listening for B press
            pairingStarted = false;
            confirmWait = false;
            break;
          }
        }
      }

      /** HANDLE COMPLETE PAIRING **/
      if (paired == true) {
        //Set group and frequency
        uBit.radio.setGroup(newGroup);
        uBit.radio.setFrequencyBand(newFrequency);
        //Update all flags
        paired = true;
        pairingStarted = false;
        confirmWait = false;
        confirmed = false;
        morseRecieved = false;
        buttonPressed = false;
        morseSent = false;
        //Display to user
        uBit.display.scroll("PAIRED");
        /* Uncomment for testing
        uBit.display.scroll(newGroup);
        uBit.display.scroll(newFrequency);
        */
        break;
      }
    }

    //Clears buffer
    uBit.radio.datagram.send("");

    //Main loop
    while (1) {
      /**
      ** HANDLE MORSE TRANSMISSION **
      **/
      //Update button up time
      uBit.sleep(50);
      buttonTime = uBit.systemTime();

      //Wait for button input
      while (buttonA.isPressed()) {
        buttonPressed = true;
      }

      //Get the button input duration
      buttonDuration = uBit.systemTime() - buttonTime;

      //Process button press
      if (buttonPressed == true) {
        //DOT Output
        if ((buttonDuration > 100) && (buttonDuration < 400)) {
          uBit.display.printAsync(DOT_IMAGE);
          transmissionBuffer += '.';
          uBit.sleep(700);
          uBit.display.clear();
        }
        //DASH output
        else if ((buttonDuration > 400) && (buttonDuration < 800)) {
          uBit.display.printAsync(DASH_IMAGE);
          transmissionBuffer += '-';
          uBit.sleep(700);
          uBit.display.clear();
        }
        //NOISE
        else if (buttonDuration > 800) {
          uBit.display.printAsync("!");
          uBit.sleep(700);
          uBit.display.clear();
        }
        //Reset variables to allow for new inputs
        buttonPressed = false;
        buttonWaiting = uBit.systemTime();
        //Update system up time
        buttonTime = uBit.systemTime();
      }

      //Input is finished if wait time met
      if (((buttonTime - buttonWaiting) > 2000) && (buttonWaiting != 0)) {
        //Get letter associated with morse input
        letter = morse->getLetter(transmissionBuffer);
        if (letter != '?') { //Only if valid morse found
          //Encrypt letter with Caeser cipher
          letter = morse->encrypt(letter);
          //Get morse code for new encrypted letter
          transmissionBuffer = morse->getMorse(letter);
          //Convert data to sendable type
          char data[transmissionBuffer.length() + 1];
          strcpy(data, transmissionBuffer.c_str());
          ManagedString dataString = data;
          //Send morse code
          uBit.radio.datagram.send(data);
          morseSent = true; //Avoid printing own sent morse
          uBit.display.printAsync(">");
          uBit.sleep(700);
          uBit.display.clear();
        } else {
          uBit.display.printAsync("?");
          uBit.sleep(700);
          uBit.display.clear();
        }
        //Reset variables to allow for new transmissions
        transmissionBuffer.clear();
        buttonWaiting = 0;
      }

      /**
      ** HANDLE INCOMING MORSE **
      **/
      //Listen for incoming radio signals
      uBit.sleep(50);
      uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);
      uBit.sleep(50);

      //If morse from another device is recieved
      if (morseRecieved == true && morseSent == false) {
        //Get letter associated with morse signal
        letter = morse->getLetter(incomingMorse);
        if (letter != '?') { //Only if valid morse found
          //Decrypt letter with Caeser cipher
          letter = morse->decrypt(letter);
        }
        //Display letter to user
        uBit.display.printAsync(letter);
        uBit.sleep(700);
        uBit.display.clear();
        //Reset variables to allow for new transmissions
        incomingMorse.clear();
        morseRecieved = false;
      } else if (morseRecieved == true && morseSent == true) {
        //Avoids sent message being processed by device that sent it
        morseSent = false;
      }
    }

    //Delete class instances and go into power efficient sleep
    delete morse;
    delete pairing;
    release_fiber();
}

void onData(MicroBitEvent e) {
  //Store recieved data
  ManagedString recievedData = uBit.radio.datagram.recv();

  /** HANDLE EMPTY DATA **/
  if (recievedData == "") {
    //Do nothing
  }

  /** HANDLE CONFIRMATION MESSAGE **/
  else if (confirmWait == true && paired == false) {
    if (recievedData == CONFIRM_MESSAGE) {
      paired = true;
      confirmWait = false;
    }
  }

  /** HANDLE POTENTIAL PAIRING DATA **/
  else if (confirmWait == false && paired == false) {
    //Wait for confirmation
    uint64_t startedWaiting = uBit.systemTime();
    while (1) {
      uBit.display.printAsync("^");
      //Wait for button input
      if (buttonA.isPressed() && buttonB.isPressed()) {
        uBit.display.clear();
        //Store transmission in correct data type
        char * dataString = (char *)recievedData.toCharArray();
        char * temp;
        //Split incoming data, and store in variables
        temp = strtok(dataString,PAIR_DELIMITER);
        newGroup = atoi(temp);
        temp = strtok(NULL,PAIR_DELIMITER);
        newFrequency = atoi(temp);
        //Update flag
        confirmed = true;
        pairingStarted = false;
        break;
      //Dont pair if user doesnt confirm within 10 seconds
      } else if ((uBit.systemTime() - startedWaiting) > 10000) {
        uBit.display.print("X");
        uBit.sleep(700);
        uBit.display.clear();
        pairingStarted = false;
        break;
      }
    }
  }

  /** HANDLE INCOMING MORSE DATA **/
  else if (paired == true) {
    //Store transmission in correct data type
    const char * data = recievedData.toCharArray();
    incomingMorse = string(data);
    morseRecieved = true; //Update flag
  }
}
