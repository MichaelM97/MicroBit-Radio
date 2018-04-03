# IoT - Challenge 3

## Contributers
- Michael McCormick (15012271)
- Jacob Davies (15012401)

## Protocol Description
This protocol first starts with a pairing sequence, to ensure the users two
MicroBits only communicate with eachother. Then will proceed to take multiple
Morse Code inputs from one BBC MicroBit, encrypts
the output using a Caesar cipher, and then transports the signal across the
Radio to another BBC MicroBit. It is then decrypted using the same cipher
and key, and the corresponding output is displayed to the user.
The protocol is used by building and loading the same hex file onto two seperate
MicroBits that are within 20 meters of each other, then using Button A to input
some morse code; followed by viewing the output on the other MicroBit.
Further details on this process can be seen below.

## Building and Loading the protocol
### 1. Clone this repository onto to your computer, and change directory into the folder:
```
git clone https://gitlab.uwe.ac.uk/m2-mccormick/IoT-Challenge3.git
cd [YOUR_FILE_PATH]/IoT-Challenge3
```
### 2. Set the target for yotta, and build the .hex file
```
yt target bbc-microbit-classic-gcc
yt build
```
### 3. Plug in your two MicroBits **one at a time**, and run the following command to load the .hex file onto each MicroBit
```
cp build/bbc-microbit-classic-gcc/source/iot-example-combined.hex /media/[YOUR_USERNAME]/MICROBIT
```

## Using the protocol
### 1. Connect the two MicroBits to a suitable power source, and ensure both are within the 20 meter range

### ADD PAIRING STEPS

### 2. You can now use either MicroBit to send a message to the other, to do this, simply enter a morse code message using Button A to send it. For example, if you wanted to send the letter 'A':
```
Tap Button A - a small dot in the centre of the screen should appear
Hold Button A for a brief moment - a small line should appear
Wait for a moment - a '>' symbol should appear, and the letter 'A' will appear on your other MicroBit
```
### Below is an image showing all possible morse code messages
![alt text](https://upload.wikimedia.org/wikipedia/commons/b/b5/International_Morse_Code.svg)
### 3. Whilst using the protocol, you will see some symbols appear. Below is a description of what each one means:
```
. - You have just entered a Dot
- - You have just entered a Dash
! - You held the button for too long (or your MicroBit is recieving noise)
> - Your message has been sent
? - You have entered an invalid morse sequence/invalid data has been recieved
```

##Brief description of the Pairing sequence
In order to reduce the amount of potential interference in a scenario where this
protocol is deployed across more than 2 MicroBits, a simple pairing
procedure has been implemented. First, the user must input the button sequence
"ABB" into either MicroBit in order to initiate the pairing sequence.
This MicroBit will then generate 3 random numbers, these will be used to set the
MicroBit Group, to set the Frequency Band, and as a unique key which will be
addded to the start of each transmission. The user must then input the button
sequence "BBA" into a seperate MicroBit within the 20 meter range, which will
cause this MicroBit to store these numbers and be paired to the originally
selected MicroBit. A confirmation signal will be sent so that both MicroBits are
ready to recieve morse code transmissions from their paired MicroBit.

## Brief description of the Caeser cipher
In order to simply encrypt the messages sent by the MicroBits, the protocol uses
a very basic Caeser cipher. In order to do this, the protocol first works out
which letter the user has just entered using morse code. Once it knows this,
the protocol shifts right 3 places through a map, which contains all of the
possible morce code inputs and their corresponding outputs. It will then send
the morse code signal of this letter that it has shifted to, rather than the
original morse sequence inputted by the user. Once the other MicroBit has finished
recieving the transmission, it will decrypt the message by shifting 3 places to
the left in the map, in order to find the correct letter the user originally
intended on displaying.

## State Diagram
![alt text](/State Diagram.png)
