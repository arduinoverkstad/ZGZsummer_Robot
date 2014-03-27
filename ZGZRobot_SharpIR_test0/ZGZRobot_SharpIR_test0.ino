#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

void setup(){
  Serial.begin(9600);
  Robot.begin();
}
void loop(){
  int val=val=(6762/(Robot.analogRead(M0)-9))-4;
  Serial.println(val);
  delay(100);
}
