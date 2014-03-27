#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

void setup(){
  Robot.begin();
  randomSeed(Robot.analogRead(D5));
  Serial.begin(9600);
}
void loop(){
  randomMove(150,500,500);
}

void randomMove(int speed, int marginMove, int marginStop){
  int directionL=random(0,2)*2-1;
  int directionR=random(0,2)*2-1;
  //Serial.println(direction);
  Robot.motorsWrite(directionL*speed,directionR*speed);
  delay(random(marginMove)+marginMove/2);
  if(marginStop){
    Robot.motorsStop();
    delay(random(marginStop)+marginStop/2);

  }
}
