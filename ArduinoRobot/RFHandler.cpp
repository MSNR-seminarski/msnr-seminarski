#include "RFHandler.hpp"


void RFHandler::enable() const
{
    _instance.enableReceive(RECEIVE_INTERRUPT_CHANNEL);
}

void RFHandler::resume()
{
    _previousCode = _receivedCode;
    _instance.resetAvailable();
}

bool RFHandler::update()
{
    if (_instance.available())
    {
        _receivedCode = _instance.getReceivedValue();
        return true;
    }

    return false;
}

int RFHandler::getReceivedCode() const
{
    return _receivedCode;
}

int RFHandler::getPreviousCode() const
{
    return _previousCode;
}
