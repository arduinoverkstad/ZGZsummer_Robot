/* Robot Logo

 This sketch demonstrates basic movement of the Robot. 
 When the sketch starts, press the on-board buttons to tell 
 the robot how to move. Pressing the middle button will 
 save the pattern, and the robot will follow accordingly. 
 You can record up to 20 commands. The robot will move for 
 one second per command.
  */

#include <ArduinoRobot.h> 
#include <Wire.h>
#include <SPI.h>

#define GO_FORWARD 1
#define GO_BACKWARDS 2
#define TURN_LEFT 3
#define TURN_RIGHT 4

int numCommands=3;
int commands[]={GO_FORWARD,TURN_RIGHT,GO_FORWARD};
int duration[]={1000,1000,1000};

void setup() {
  Robot.begin();
  delay(1000);
}

void loop() {  
  executeCommands(); // follow orders
  
  while(true);
  
}



// run through the array and move the robot
void executeCommands() {
  // read through the array and move accordingly
  for(int i=0; i<numCommands; i++) {
    switch(commands[i]) {
      case TURN_LEFT:
        Robot.motorsWrite(-255, 255);
        break;
      case TURN_RIGHT:
        Robot.motorsWrite(255, -255);
        break;
      case GO_FORWARD:
        Robot.motorsWrite(255, 255);
        break;
      case GO_BACKWARDS:
        Robot.motorsWrite(-255, -255);
        break;
      case BUTTON_NONE:
        return;
    }
    delay(duration[i]);
    
    // stop moving for a second
    Robot.motorsWrite(0, 0);
    delay(1000);
  }
}

