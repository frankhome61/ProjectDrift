#pragma once
#include "thruster.h"
unsigned char switchCommandType(unsigned char package);
unsigned char switchPackageType(unsigned char package);
void processInPackage(unsigned char package);
void serialInit();
/*
input1 input2
0000xxxx 1nnnnnnn
xxx:
000 FORWARD_STARBOARD
001 FORWARD_PORT
010 BOW_STARBOARD
011 BOW_PORT
100 AFT_STARBOARD
101 AFT_PORT
110 TRANS_BOW
111 TRANS_AFT
nnnnnnn:
0-127 ->1500-128   1500+128

c--> checksum for both packages !!!to odd!!

->1500
*/
