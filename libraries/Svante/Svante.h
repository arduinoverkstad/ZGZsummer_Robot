#ifndef SVANTE_H
#define SVANTE_H

#define MOTOR_L1 10
#define MOTOR_L2 9
#define MOTOR_R1 5
#define MOTOR_R2 6

#define TRIM A3

#define IR_1 A2
#define IR_2 A1
#define IR_3 A0



#define MIN_MOTOR_VAL 70
#define MOTOR_CALIB_MULTI 1000.0

#define DEBUG
//#define DEBUG_SPEED

struct SpeedPair{
	int speed1;
	int speed2;
};

class Svante{
	public:
		Svante();
		void begin(int motorsDiff=0);
		void setMotorsDiff(int diff);

		void go(int speedLeft,int speedRight);
		void stop();
		
	private:
		float leftMotorMulti,rightMotorMulti;
		void initMotors();
		void motorsWrite(int speedL1,int speedL2, int speedR1, int speedR2);
		int getTrim();
		SpeedPair procSpeed(int speedRaw,float motorPow);

};

extern Svante robot;

#endif