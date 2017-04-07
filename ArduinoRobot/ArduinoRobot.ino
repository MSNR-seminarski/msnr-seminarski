#include <ArduinoRobot.h>
#include <RCSwitch.h>
#include "RFHandler.hpp"
#include "Alarm.hpp"


#define MOVE_FORWARD 		3
#define MOVE_BACKWARDS 		4
#define TURN_LEFT 			1
#define TURN_RIGHT 			2
#define HORN 				6
#define ALARM 				7
#define STOP_MOVING 		63

static void playHorn();
static void processResult(int);
static void moveRobot(float, float);
static void toggleHorn();
static void toggleLight();
static void toggleAlarm();

Alarm alarm;
RFHandler rfRx;

//-----------------------------------------------------------------------------
// Setup
//-----------------------------------------------------------------------------
void setup()
{
	Robot.begin();
	Robot.beginSpeaker();
	rfRx.enable();
}

//-----------------------------------------------------------------------------
// Loop
//-----------------------------------------------------------------------------
void loop()
{
	alarm.update();

	if (rfRx.update())
	{
		processResult(rfRx.getReceivedCode());
	}
	rfRx.resume();
}

void processResult(int receivedCode)
{
	switch (receivedCode)
	{
		case MOVE_FORWARD:
			moveRobot(1, 1, 150);
			break;
		case MOVE_BACKWARDS:
			moveRobot(-1, -1, 150);
			break;
		case TURN_LEFT:
			moveRobot(-0.5, 0.5, 230);
			break;
		case TURN_RIGHT:
			moveRobot(0.5, -0.5, 230);
			break;
		case STOP_MOVING:
			Robot.motorsStop();
			break;
		case HORN:
			toggleHorn();
			break;
		case ALARM:
			toggleAlarm();
			break;
	}
}

void toggleHorn()
{
	Robot.beep(BEEP_SIMPLE);
}

void toggleAlarm()
{
	alarm.setAlarmState(!alarm.getAlarmState(), Robot.compassRead());
}

void moveRobot(float leftMotorDirection, float rightMotorDirection, float motorSpeed)
{
	Robot.motorsWrite(motorSpeed * leftMotorDirection, motorSpeed * rightMotorDirection);
}

