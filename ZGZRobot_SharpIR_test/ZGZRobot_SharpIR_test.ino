#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

#include <Servo.h> 
 
Servo myServo;  // create servo object to control a servo 
 
int scanCount=0;
 
int servoPos=0;
int target=0;
const int servoPosMin=30;
const int servoPosMax=150;

const int valSample_len=5;
const int detectionRange=30;

void setup() 
{ 
  Serial.begin(9600);
  Robot.begin();
  myServo.attach(D1);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
  scan();
  Serial.println(scanCount);
  int error=target-90;
  //Serial.println(error);
  delay(5);
}

void scan(){
  int distance=getValAvg();
  //Serial.println(distance);
  target=servoPos;
  if(distance<detectionRange){
    //detected
    //target=servoPos;
    scanCount++;
    if(servoPos>servoPosMin){
      servoPos--;
      myServo.write(servoPos);
    }
    
    
  }else{
    //not detected
    //target=90;
    if(scanCount>0)scanCount--;
    if(servoPos<servoPosMax){
      servoPos++;
      myServo.write(servoPos);

    }else{

      servoPos=servoPosMin;
      myServo.write(servoPos);

      delay(20);
    }
  }
}
int getValAvg(){
  int sum=0;
  for(int i=0;i<valSample_len;i++){
    sum+=getDistance();
  }
  int valAvg=sum/valSample_len;
  return valAvg;
}
int getDistance(){
  int val=abs((6762/(Robot.analogRead(M0)-9))-4);
  return val;
}
