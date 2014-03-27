#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

#include <pitches.h>


const int margin_move=500;
const int margin_stop=500;
const int robot_speed=150;
const int margin_spin=2000;

int randomMove_chance=60;
int speak_chance=30;
int spin_chance=10;

int numNotes=9;
int notes[]={NOTE_C4,0,NOTE_E4,0,NOTE_D4,0,NOTE_F4,0,NOTE_C4};
int durations[]={160,20,80,20,80,20,80,20,320};
int piezoPin=BUZZ;


void setup(){
  Robot.begin();
  randomSeed(Robot.analogRead(D5));
  Serial.begin(9600);
}
void loop(){
  
  int actionDice=random(100);
  if(actionDice<randomMove_chance){
    randomMove();
  }else if(actionDice<randomMove_chance+speak_chance){
    speak();
  }else if(actionDice<randomMove_chance+speak_chance+spin_chance){
    spin();
  }
  //speak();
  //delay(2000);
}

//utility
int getRandomTime(int margin){
  return random(margin)+margin/2;
}


//behaviors
void randomMove(){
  int directionL=random(0,2)*2-1;
  int directionR=random(0,2)*2-1;
  //Serial.println(direction);
  Robot.motorsWrite(directionL*robot_speed,directionR*robot_speed);
  delay(getRandomTime(margin_move));
  Robot.motorsStop();
  delay(getRandomTime(margin_stop));
}

void spin(){
  int direction=random(0,2)*2-1;
  Robot.motorsWrite(direction*255,-direction*255);
  delay(getRandomTime(margin_spin));
  Robot.motorsStop();
  delay(getRandomTime(margin_stop));

}
void speak(){
  for(int i=0;i<numNotes;i++){
    tone(piezoPin,notes[i],durations[i]);
    delay(durations[i]);
  }
  delay(100);
}

