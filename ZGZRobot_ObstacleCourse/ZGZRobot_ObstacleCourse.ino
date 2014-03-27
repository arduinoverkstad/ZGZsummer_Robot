#include <IRremote.h>
#include <IRremoteTools.h>
#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

const int RECV_PIN = D1;
long signalTimer;

const unsigned long TIME_OUT=200;
const int ROBOT_SPEED=100;

void setup()
{
  Robot.begin();
  Serial.begin(9600);
  beginIRremote(RECV_PIN); // Start the receiver
}

void loop() {
  if (IRrecived()) {
    unsigned long command=getIRresult();
    //Serial.println(command,HEX);

    if(command!=REMOTE_CONTINUE){
      //currentCommand=newCommand;
      switch(command){
        case REMOTE_UP:
          Robot.motorsWrite(ROBOT_SPEED,ROBOT_SPEED);
          break;
        case REMOTE_DOWN:
          Robot.motorsWrite(-ROBOT_SPEED,-ROBOT_SPEED);
          break;
        case REMOTE_LEFT:
          Robot.motorsWrite(-ROBOT_SPEED,ROBOT_SPEED);
          break;
        case REMOTE_RIGHT:
          Robot.motorsWrite(ROBOT_SPEED,-ROBOT_SPEED);
          break;
      }

    }
    signalTimer=millis();
    resumeIRremote(); // Receive the next value
  }
  
  if(millis()-signalTimer>=TIME_OUT){
    Robot.motorsStop();
  }
}
