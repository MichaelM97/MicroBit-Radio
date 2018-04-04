/**
 * File: main.cpp
 * Author: Michael McCormick
 * Date: 03-04-2018
 * Desc: Basic pairing & transmission protocol for morse code sent across 2
 * microbits connected via the radio. Implements a basic encryption cypher.
 * Copyright: University of West of England 2018
 */
#include "MicroBit.h"
#include "morse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>

//Timings used for distinguishing between dot/dash transmissions
#define DOT_TIME 250
#define DASH_TIME 500

//Variable that is sent/recieved to confirm pairing
#define CONFIRM_MESSAGE "confirm"

//Variable used for splitting pairing data string
#define PAIR_DELIMITER ','

//Flags used to track pairing status
bool pairingStarted, paired;

//Variables used for pairing
int newGroup, newFrequency, key;

using namespace std;

/* Function Prototypes */
//Starts the pairing procedure
void pairingStart(MicroBitEvent e);

//Used to access microbit
MicroBit uBit;

//Images used for displaying dot/dash
MicroBitImage DOT_IMAGE("0,0,0,0,0\n0,0,0,0,0\n0,0,255,0,0\n0,0,0,0,0\n0,0,0,0,0\n");
MicroBitImage DASH_IMAGE("0,0,0,0,0\n0,0,0,0,0\n0,255,255,255,0\n0,0,0,0,0\n0,0,0,0,0\n");

//Button events
MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);

int main()
{
    //Initialise the micro:bit runtime and radio
    uBit.init();
    uBit.radio.enable();

    //Create instance of classes
    MorseClass* morse = new MorseClass();
    PairingClass* pairing = new PairingClass();

    //Variables
    bool buttonPressed = false, incomingSignal = false;
    uint64_t buttonTime, buttonDuration, buttonWaiting = 0,
      signalTime, signalDuration, signalWaiting = 0;
    string transmissionBuffer;
    char letter;

    //Set flags
    paired = false;
    pairingStarted = false;

    //Handle pairing procedure
    while (paired == false) {
      //Listen for button press or radio data
      uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, pairingStart);
      uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onFirstData);

      /** HANDLE START PAIRING **/
      if (pairingStart == true) {
        //Get new random variables
        newGroup = pairing.randomInt(0, 255, uBit.systemTime());
        newFrequency = pairing.randomInt(0, 100, uBit.systemTime());
        key = pairing.randomInt(0, 500, uBit.systemTime());

        //Send variables across radio, merge using global delimiter
        ManagedString randomNums = newGroup.str() + PAIR_DELIMITER +
         newFrequency.str() + PAIR_DELIMITER + key.str() + PAIR_DELIMITER;
        uBit.radio.datagram.send(randomNums);
        pairingStart = false;

        //Wait for confirmation
        uint64_t startedWaiting = uBit.systemTime();
        while (1) {
          uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onConfirm);
          if (paired == true) {
            uBit.display.scroll("PAIRED"); //Will continue to MorseCode handling
            break;
          } else if ((uBit.systemTime() - startedWaiting) > 10000) {
            uBit.display.scroll("ERROR"); //Will go back to listening for B press
            break;
          }
        }
      }

      /** HANDLE COMPLETE PAIRING **/
      if (paired == true) {
        uBit.radio.setGroup(newGroup);
        uBit.radio.setFrequencyBand(newFrequency);
      }
    }

    //Main infinite loop
    while (1) {
      //Update button up time
      buttonTime = uBit.systemTime();

      /** HANDLE MORSE TRANSMISSION **/
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
          //Send morse code
          uBit.radio.datagram.send(key.str() + transmissionBuffer);
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

      /** HANDLE INCOMING MORSE **/
      //Update signal up time
      signalTime = uBit.systemTime();

      //Wait for signal from Pin 1
      while (P1.getDigitalValue() == 1) {
        incomingSignal = true;
      }

      //Get the incoming signal duration
      signalDuration = uBit.systemTime() - signalTime;

      //Process incoming signal
      if (incomingSignal == true) {
        //DOT input
        if ((signalDuration > 100) && (signalDuration < 400)) {
          transmissionBuffer += '.';
        }
        //DASH input
        else if ((signalDuration > 400) && (signalDuration < 800)) {
          transmissionBuffer += '-';
        }
        //NOISE
        else if (signalDuration > 800) {
          uBit.display.printAsync("!");
          uBit.sleep(700);
          uBit.display.clear();
        }
        //Reset variables to allow for new incoming signals
        incomingSignal = false;
        signalWaiting = uBit.systemTime();
        //Update system up time
        signalTime = uBit.systemTime();
      }

      //Incoming signal is finished if wait time met
      if (((signalTime - signalWaiting) > 2000) && (signalWaiting != 0)) {
        //Get letter associated with morse signal
        letter = morse->getLetter(transmissionBuffer);
        if (letter != '?') { //Only if valid morse found
          //Decrypt letter with Caeser cipher
          letter = morse->decrypt(letter);
        }
        //Display letter to user
        uBit.display.printAsync(letter);
        uBit.sleep(700);
        uBit.display.clear();
        //Reset variables to allow for new transmissions
        transmissionBuffer.clear();
        signalWaiting = 0;
      }
    }

    //Delete class instances and go into power efficient sleep
    delete morse;
    delete pairing;
    release_fiber();
}

void pairingStart(MicroBitEvent e) {
	pairingStart = true;
}

void onConfirm(MicroBitEvent e) {
  ManagedString recievedData = uBit.radio.datagram.recv();
  if (recievedData == CONFIRM_MESSAGE) {
    paired = true;
  }
}

void onFirstData(MicroBitEvent e) {
  try {
    ManagedString recievedData = uBit.radio.datagram.recv();
    //Split incoming data, and store in variables
    newGroup = strtok(recievedData,PAIR_DELIMITER);
    newFrequency = strtok(recievedData,PAIR_DELIMITER);
    key = strtok(recievedData,PAIR_DELIMITER);
    //Send confirm message and update pairing status
    uBit.radio.datagram.send(CONFIRM_MESSAGE);
    paired = true;
  } catch (...) {
    /*
      There was an error with handling the data, therefore recieved transmission
      was not sent from this matching protocol
    */
    paired = false;
  }
}
