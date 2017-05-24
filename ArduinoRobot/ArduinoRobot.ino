#include <ArduinoRobot.h>
#include <RCSwitch.h>
#include "RFHandler.hpp"
#include "Alarm.hpp"

#define MOVE_FORWARD        0b11000111
#define MOVE_BACKWARDS      0b11001111
#define TURN_LEFT           0b11000001
#define TURN_RIGHT          0b11000011
#define START_HORN          0b11011001
#define ALARM               0b11011101
#define STOP_MOVING         0b11011111
#define LIGHT               0b11010001
#define STOP_HORN           0b11100101

static void processResult(int);
static void moveRobot(float, float);
static void toggleHorn();
static void toggleLight();
static void toggleAlarm();
static void startHorn();
static void stopHorn();

Alarm alarm;
RFHandler rfRx;
bool lightsStatus = false;

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
        if (rfRx.getPreviousCode() != rfRx.getReceivedCode())
        {
            processResult(rfRx.getReceivedCode());
            rfRx.resume();
        }
    }
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
        case START_HORN:
            startHorn();
            break;
        case STOP_HORN:
            stopHorn();
            break;
        case ALARM:
            toggleAlarm();
            break;
        case LIGHT:
            toggleLight();
            break;
    }
}

void startHorn()
{
    Robot.beep(BEEP_LONG);
}

void stopHorn()
{
    Robot.beep(BEEP_LONG);
}

void toggleLight()
{
    if (lightsStatus)
    {
        lightsStatus = false;
        Robot.digitalWrite(TKD1, lightsStatus);
    }
    else
    {
        lightsStatus = true;
        Robot.digitalWrite(TKD1, lightsStatus);
    }
}

void toggleAlarm()
{
    alarm.setAlarmState(!alarm.getAlarmState(), Robot.compassRead());
}

void moveRobot(float leftMotorDirection, float rightMotorDirection, float motorSpeed)
{
    Robot.motorsWrite(motorSpeed * leftMotorDirection, motorSpeed * rightMotorDirection);
}

