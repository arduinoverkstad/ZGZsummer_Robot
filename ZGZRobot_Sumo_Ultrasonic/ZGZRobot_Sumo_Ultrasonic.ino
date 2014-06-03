#include <Svante.h>
#include <EEPROM.h>
 
int currentMode;//0:search, 1:track, 2:attack, 3:survive
 
int target=0;
int trackCount=0;
boolean tracked=false;
const int trackCountMax=20;
const int trackCountThreshold=10;

const int pingR=DP4;
const int pingL=DP8;

const int valSample_len=1;
const int detectionRange=30;  //30cm

const int searchSpeed=60;
const int trackSpeed=50;
const int attackSpeed=80;
const int surviveSpeed=60;
const float attackOffset=0.5;
const float trackOffset=0.3;
int edgeValue=200;

int error;

void setup() 
{ 
  Serial.begin(9600);
  robot.begin();

  currentMode=0;
  searchMode();
} 
 
void loop() 
{ 
  scan();
  if(trackCount>trackCountThreshold)
    tracked=true;
  else
    tracked=false;
    
  //Serial.println(tracked);

  //Serial.println(currentMode);
  
  modeManager();
  delay(5);
}
void modeManager(){
  if(onEdge()){
    currentMode=3;
    surviveMode();
    return;
  }
  if(!tracked){
    if(currentMode!=0){
      currentMode=0;
      searchMode();
    }
  }else{
    if(abs(error)<30){
      currentMode=2;
      attackMode();
      
    }else{
      currentMode=1;
      trackMode();
    }
  }
}
void scan(){
  int distanceL=getValAvg(pingL);
  int distanceR=getValAvg(pingR);
  /*
  Serial.print(distanceL);
  Serial.print(" ");
  Serial.println(distanceR);
  */
  boolean trackedL=distanceL<detectionRange?true:false;
  boolean trackedR=distanceR<detectionRange?true:false;
  
  if(trackedL||trackedR){
    if(trackCount<trackCountMax) trackCount++;
  }else{
    if(trackCount>0) trackCount--;
  }
  
  target=90;
  if(trackedL)target-=90;
  if(trackedR)target+=90;
}
int getValAvg(int sensorPin){
  int sum=0;
  for(int i=0;i<valSample_len;i++){
    sum+=getDistance(sensorPin);
  }
  int valAvg=sum/valSample_len;
  return valAvg;
}
int getDistance(int sensorPin){
  pinMode(sensorPin,OUTPUT);
  digitalWrite(sensorPin,LOW);
  delayMicroseconds(2);
  digitalWrite(sensorPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(sensorPin, LOW);
  
  pinMode(sensorPin, INPUT);
  int duration = pulseIn(sensorPin, HIGH, 11800);
  return getCMs(duration);
}
long getCMs(int ms){
  if(ms!=0){
    return ms/29/2;
  }else{
    return 1000;
  }
}

boolean onEdge(){
  for(int i=0;i<5;i++){
    if(robot.getIRArray(i)<edgeValue)
      return true;
  }
  return false;
}

void searchMode(){
  robot.go(searchSpeed,-searchSpeed);
}
void trackMode(){
  error=target-90;
  int res=error*trackOffset;
  if(res<0){
    res-=trackSpeed;
  }else if(res>0){
    res+=trackSpeed;
  }
  robot.go(res,-res);
}
void attackMode(){
  error=target-90;
  int res=error*attackOffset;
  
  robot.go(res+attackSpeed,attackSpeed-res);
}
void surviveMode(){
  robot.go(-surviveSpeed,-surviveSpeed);
  delay(500);
}
