#pragma once
#include "Arduino.h"
#include <Servo.h>
extern Servo THRUSTERS[8];
extern Servo& FORWARD_STARBOARD;// pin 2
extern Servo& FORWARD_PORT;// 3
extern Servo& BOW_STARBOARD;// 4
extern Servo& BOW_PORT;// 5
extern Servo& AFT_STARBOARD;// 6
extern Servo& AFT_PORT;// 7
extern Servo& TRANS_BOW;// 8
extern Servo& TRANS_AFT;// 9
void sendThrusterSpeed(unsigned char selector, short speed);
void thrusterTest();
void thrustersInit();
int   getThrusterServoMs(unsigned char in_data);
