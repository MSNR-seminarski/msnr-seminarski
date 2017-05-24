#ifndef __ALARM_HPP__
#define __ALARM_HPP__

#define COMPASS_REFRESH_PERIOD  3000


class Alarm
{
public:
    Alarm();

    void update();
    void setAlarmState(const bool alarmState, const int compassValue);
    bool getAlarmState() const;

private:
    bool _alarmState;
    int _lastCompassValue;
    unsigned int _interval;
    unsigned long _previousMillis;
};

#endif // __ALARM_HPP__
