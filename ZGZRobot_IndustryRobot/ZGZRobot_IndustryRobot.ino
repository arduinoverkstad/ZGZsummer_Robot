#include <Svante.h>
void setup(){
	robot.begin();
	delay(1000);
	robot.lineFollowCalibrate();
	robot.lineFollowConfig(10,0,10,30);
	delay(1000);

}
void loop(){
	robot.startLineFollow();
	//Run the logo sequence here
	robot.go(100,100);	//move forward to engage the target
	delay(500);
	robot.go(50,-50);	//turn around with the target grabbed
	delay(200);
	robot.go(100,100);	//push the target out
	delay(500);
	robot.go(-100,-100);	//the same way back
	delay(500);
	robot.go(-50,50);	//turn around, facing the track
	delay(200);
	robot.go(100,100);	//engage the track
	delay(500);
}