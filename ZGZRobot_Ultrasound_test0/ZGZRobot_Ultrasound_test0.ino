#include<ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

const int pingR=D0;
const int pingL=D2;

void setup(){
  Robot.begin();
  Serial.begin(9600);
}
void loop(){
  int disL=getDis(pingL);
  int disR=getDis(pingR);
  Serial.print(disL);
  Serial.print(" ");
  Serial.println(disR);
  
  
  delay(100);
}

int getDis(int sensorPin){
  pinMode(sensorPin,OUTPUT);
  digitalWrite(sensorPin,LOW);
  delayMicroseconds(2);
  digitalWrite(sensorPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(sensorPin, LOW);
  pinMode(sensorPin, INPUT);
  int duration = pulseIn(sensorPin, HIGH);
  return getCMs(duration);
}
long getCMs(int ms){
  return ms/29/2;
}
