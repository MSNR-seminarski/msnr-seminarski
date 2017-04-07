#ifndef __RFHANDLER_HPP__
#define __RFHANDLER_HPP__

#include <RCSwitch.h>

#define RECEIVE_INTERRUPT_CHANNEL 4


class RFHandler
{
public:
	void enable() const;
	void resume() const;
	int getReceivedCode() const;
	bool update();

private:
	int _receivedCode;
	RCSwitch _instance;
};

#endif // __RFHANDLER_HPP__
