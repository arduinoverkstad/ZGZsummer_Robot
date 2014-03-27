/*
 IR array
 
 Read the analog value of the IR sensors at the 
 bottom of the robot. The also-called line following 
 sensors are a series of pairs of IR sender/receiver
 used to detect how dark it is underneath the robot.

 The information coming from the sensor array is stored
 into the Robot.IRarray[] and updated using the Robot.updateIR()
 method.
 
 Circuit:
 * Arduino Robot
 
 created 1 May 2013
 by X. Yang
 modified 12 May 2013
 by D. Cuartielles
 
 This example is in the public domain
 */

#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

int sensor_white[5];
int sensor_black[5];

int sum=0;

long calib_time=5000;

void setup(){
  // initialize the robot
  Robot.begin();

  // initialize the serial port
  Serial.begin(9600);
  
  
  while(Serial.read()==-1);
  calibrate();
}

void loop(){
  // store the sensor information into the array 
  Robot.updateIR();

  // iterate the array and print the data to the Serial port
  for(int i=0; i<5; i++){
    sum+=map(Robot.IRarray[i],sensor_black[i],sensor_white[i],0,127);
    //Serial.print(Robot.IRarray[i]);
    //Serial.print(" ");
  }
  Serial.print("sum: ");
  Serial.println(sum);
  //sum/=5;
  sum=0;
  //Serial.println("");
}

void calibrate(){
  for(int i=0;i<5;i++){
    sensor_black[i]=1023;
    sensor_white[i]=0;
  }
  Serial.println("Start Calibration");
  long begin_time=millis();
  while(millis()-begin_time<calib_time){
    Robot.updateIR();
    for(int i=0;i<5;i++){
      if(Robot.IRarray[i]==0)break;
      
      if(Robot.IRarray[i]>sensor_white[i]){
        sensor_white[i]=Robot.IRarray[i];
      }
      if(Robot.IRarray[i]<sensor_black[i]){
        sensor_black[i]=Robot.IRarray[i];
      }
    }
  }
  
  Serial.println("Result");
  Serial.println("white:");
  for(int i=0;i<5;i++){
    Serial.print(sensor_white[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.println("Black");
  for(int i=0;i<5;i++){
    Serial.print(sensor_black[i]);
    Serial.print(" ");
  }
  Serial.println();
  
  while(Serial.read()==-1);
  
}
