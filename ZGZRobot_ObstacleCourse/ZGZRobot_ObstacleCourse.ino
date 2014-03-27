#include <IRremote.h>
#include <IRremoteTools.h>
#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

int RECV_PIN = D1;
unsigned long currentCommand=0;
long signalTimer;

const int timerMax=200;
const int speed=100;

void setup()
{
  Robot.begin();
  Serial.begin(9600);
  beginIRremote(RECV_PIN); // Start the receiver
}

void loop() {
  if (IRrecived()) {

    signalTimer=millis();
    unsigned long newCommand=getIRresult();
      Serial.println(newCommand,HEX);

    if(newCommand!=REMOTE_CONTINUE){
      currentCommand=newCommand;
      switch(currentCommand){
        case REMOTE_UP:
          Robot.motorsWrite(speed,speed);
          break;
        case REMOTE_DOWN:
          Robot.motorsWrite(-speed,-speed);
          break;
        case REMOTE_LEFT:
          Robot.motorsWrite(-speed,speed);
          break;
        case REMOTE_RIGHT:
          Robot.motorsWrite(speed,-speed);
          break;
      }

    }
    resumeIRremote(); // Receive the next value
    
  }
  
  if(millis()-signalTimer>=timerMax){
    currentCommand=0;
    Robot.motorsStop();
  }
}
