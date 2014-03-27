#include <IRremote.h>
#include <IRremoteTools.h>
#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

const int RECV_PIN = D1;
long signalTimer;

#define IDLE_MODE 0
#define MOVE_MODE 1
#define SERVO_MODE 2

int currentMode=IDLE_MODE;
int currentSDir;//current servo direction


const unsigned long TIME_OUT=200;
const int ROBOT_SPEED=100;

void setup()
{
  Robot.begin();
  Serial.begin(9600);
  beginIRremote(RECV_PIN); // Start the receiver
}

void loop() {
  getCommand();
  
  checkTimer();
}


void getCommand(){
  if (IRrecived()) {
    unsigned long command=getIRresult();
    //Serial.println(command,HEX);

    if(command!=REMOTE_CONTINUE){
      switch(command){
        case REMOTE_UP:
          moveRobot(ROBOT_SPEED,ROBOT_SPEED);
          break;
        case REMOTE_DOWN:
          moveRobot(-ROBOT_SPEED,-ROBOT_SPEED);
          break;
        case REMOTE_LEFT:
          moveRobot(-ROBOT_SPEED,ROBOT_SPEED);
          break;
        case REMOTE_RIGHT:
          moveRobot(ROBOT_SPEED,-ROBOT_SPEED);
          break;
        case REMOTE_PLUS:
          moveServo(false, 1);
          break;
        case REMOTE_MINUS:
          moveServo(false, -1);
          break;
      }
    }else{
      repeat();
    }
    signalTimer=millis();
    resumeIRremote(); // Receive the next value
  }
}
void moveRobot(int speedL, int speedR){
  stopAll();
  currentMode=MOVE_MODE;
  Robot.motorsWrite(speedL,speedR);
}
void moveServo(boolean iRepeat, int sDirection){
  if(!iRepeat){
    stopAll();
    currentMode=SERVO_MODE;
    currentSDir=sDirection;
  }
  Serial.print("Servo move ");
  Serial.println(currentSDir);
//move servo here
}
void repeat(){
  switch(currentMode){
    case MOVE_MODE:
      break;
    case SERVO_MODE:
      moveServo(false,currentSDir);
      break;
  }
}
void stopAll(){
  //stop all current actions
  Robot.motorsStop();
}

void checkTimer(){
  if(millis()-signalTimer>=TIME_OUT){
    stopAll();
    currentMode=IDLE_MODE;
  }
}
