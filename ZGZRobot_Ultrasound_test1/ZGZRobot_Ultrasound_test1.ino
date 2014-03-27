//#include<ArduinoRobot.h>
//#include <Wire.h>
//#include <SPI.h>

const int trig=11;
const int echo=11;

void setup(){
//  Robot.begin();
  Serial.begin(9600);
}
void loop(){
  int disL=getDis(trig,echo);
  Serial.println(disL);
  
  delay(100);
}

int getDis(int triggerPin,int sensorPin){
  pinMode(triggerPin,OUTPUT);
  digitalWrite(triggerPin,LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPin, LOW);
  pinMode(sensorPin, INPUT);
  int duration = pulseIn(sensorPin, HIGH,11800);
  //return duration;
  return getCMs(duration);
}
long getCMs(int ms){
  return ms/29/2;
}
