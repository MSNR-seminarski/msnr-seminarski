#ifndef __RFHANDLER_HPP__
#define __RFHANDLER_HPP__

#include <RCSwitch.h>

#define RECEIVE_INTERRUPT_CHANNEL 4
#define INIT_CODE 5234

class RFHandler
{
public:
    void enable() const;
    int getReceivedCode() const;
    int getPreviousCode() const;
    void resume();
    bool update();

private:
    int _receivedCode;
    int _previousCode = INIT_CODE;
    RCSwitch _instance;
};

#endif // __RFHANDLER_HPP__
