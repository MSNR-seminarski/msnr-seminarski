#include "Arduino.h"
#include "ArduinoRobot.h"
#include "Alarm.hpp"


Alarm::Alarm() :
	_interval(COMPASS_REFRESH_PERIOD), _previousMillis(0), _alarmState(false) {}

void Alarm::update()
{
	if (_alarmState)
	{
		unsigned long currentMillis = millis();

		if ((currentMillis - _previousMillis >= _interval))
		{
			int compass = Robot.compassRead();

			if (abs(_lastCompassValue - compass) > 10)
			{
				Robot.beep(BEEP_SIMPLE);
			}

			_lastCompassValue = compass;
			_previousMillis = currentMillis;
		}
	}
}

void Alarm::setAlarmState(bool alarmState, int compassValue)
{
	_alarmState = alarmState;
	_lastCompassValue = compassValue;
}

bool Alarm::getAlarmState() const
{
	return _alarmState;
}
