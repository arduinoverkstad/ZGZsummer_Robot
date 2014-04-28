#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

#include <pitches.h>


const int margin_move=500;
const int margin_stop=500;
const int robot_speed=150;
const int margin_spin=1000;

const int blinkTime=500;
const int blinkSpeed=10;
const int ledPin=D1;

int randomMove_chance=60;
int speak_chance=0;
int spin_chance=10;
int blink_chance=30;

int numNotes=9;
int notes[]={NOTE_C4,0,NOTE_E4,0,NOTE_D4,0,NOTE_F4,0,NOTE_C4};
int durations[]={160,20,80,20,80,20,80,20,320};
int piezoPin=BUZZ;


volatile int blinkPinStat=0;
unsigned long blinkTimer=0;


void setup(){
  Robot.begin();
  randomSeed(Robot.analogRead(D5));
  Serial.begin(9600);
  initBlink();
}
void loop(){
  int actionDice=random(100);
  int diceSum=0;
  
  diceSum+=randomMove_chance;
  if(actionDice<diceSum){
    randomMove();
    return;
  }
  
  diceSum+=speak_chance;
  if(actionDice<diceSum){
    speak();
    return;
  }
  
  diceSum+=spin_chance;
  if(actionDice<diceSum){
    spin();
    return;
  }
  
  diceSum+=blink_chance;
  if(actionDice<diceSum){
    doBlink();
    return;
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

void initBlink(){
  //pinMode(ledPin,OUTPUT);
  
  cli();
  TCCR1A=0;
  TCCR1B=0;
  TCNT1=0;
  
  OCR1A=15624*(1.0/blinkSpeed);
  TCCR1B |= (1<<WGM12);
  TCCR1B |= (1<<CS12) | (1<<CS10);
  sei();

}

void doBlink(){
  blinkTimer=millis();
  cli();
  TCNT1=0;
  TIMSK1 |= (1<<OCIE1A);
  sei();
}
ISR(TIMER1_COMPA_vect){
  if(millis()-blinkTimer<blinkTime){
    blinkPinStat=!blinkPinStat;
  }else{
    blinkPinStat=LOW;
    cli();
    TIMSK1 &= (~(1<<OCIE1A));
    sei();
  }
  Robot.digitalWrite(ledPin,blinkPinStat);

}
