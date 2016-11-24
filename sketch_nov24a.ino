#include "thruster.h"
#include "serial.h"
int lights[] = {6,9,10,11};
void setup(){
  analogWrite(1,1);
 Serial.begin(9600); 
}
void loop(){
  if (Serial.available() > 0){
    byte buffer;
    while (Serial.available()){
      buffer=Serial.read();}
      processInPackage(buffer);
  }
  
  
  
}
