# **ProjectDrift**

## introduction

This is the ELAC Robotics club project for RoboSub.

It is (will be) written in C, C++, Python.

## Documentation

### Serial Network Protocol 

The Serial communication is between the Arduino and the motherboard.

Its Protocol has two goals: return the sensor results and control the thrusters and other motor connected devices on the Arduino.

#### Control the Arduino

There are two package types, all must be **ONE BYTE**.

+  Selector:
+  Selector is the package that select a device to control
   + it MUST begin with 0.  For example: 0b00000100
   + Its last four digits are considered the id for the device
     + This can be modified later
+  instrustion:
   + Instruction is the package that contains the actual data to give the device
   + it MUST begin with 1. For example: 0b10000100
   + The last 7 digits are considered the data to be given to the device selected

By default, a null device is selected.



It's written in the Serial.h:

> input1 input2

> 0000xxxx 1nnnnnnn

> xxx:

> 000 FORWARD_STARBOARD

> 001 FORWARD_PORT

> 010 BOW_STARBOARD

> 011 BOW_PORT

> 100 AFT_STARBOARD

> 101 AFT_PORT

> 110 TRANS_BOW

> 111 TRANS_AFT

> nnnnnnn:

> 0-127 ->1500-128   1500+128



The program which controls the Arduino Should **optimize the Serial data** by caching the last selector.

Also it should keep track of the changes of the actual instructions to each of the device. And **only send the last instruction**.

#### Reading the sensor data

\* this part of the Protocol is not detailed considered

the Arduino should **keep returning** all the sensor data with the same Protocol controlling it.
