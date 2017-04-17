#include <RCSwitch.h>

#define CODE_TX_LEFT        1
#define CODE_TX_RIGHT       2
#define CODE_TX_FORWARD     3
#define CODE_TX_BACKWARD    4
#define CODE_TX_LIGHT       8
#define CODE_TX_HORN        6
#define CODE_TX_ALARM       7
#define CODE_TX_STOP        63

#define CODE_RX_LEFT        1
#define CODE_RX_STOP        5
#define CODE_RX_RIGHT       2
#define CODE_RX_FORWARD     3
#define CODE_RX_BACKWARD    4
#define CODE_RX_HORN        6
#define CODE_RX_ALARM       7
#define CODE_RX_LIGHT       8

#define MESSAGE_LENGTH      8
#define DELAY_TIME          1
#define TRANSMIT_CHANNEL    10
#define SERIAL_BAUD_RATE    9600

//-----------------------------------------------------------------------------
// setup()
//-----------------------------------------------------------------------------
RCSwitch rfTx = RCSwitch();

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);
    rfTx.enableTransmit(TRANSMIT_CHANNEL);
}

//-----------------------------------------------------------------------------
// loop()
//-----------------------------------------------------------------------------
void loop()
{
    static byte receivedData;

    if (Serial.available())
    {
        receivedData = Serial.read();
        switch (receivedData)
        {
            case CODE_RX_LEFT :
                rfTx.send(CODE_TX_LEFT, MESSAGE_LENGTH);
                break;
            case CODE_RX_RIGHT :
                rfTx.send(CODE_TX_RIGHT, MESSAGE_LENGTH);
                break;
            case CODE_RX_FORWARD :
                rfTx.send(CODE_TX_FORWARD, MESSAGE_LENGTH);
                break;
            case CODE_RX_BACKWARD :
                rfTx.send(CODE_TX_BACKWARD, MESSAGE_LENGTH);
                break;
            case CODE_RX_HORN :
                rfTx.send(CODE_TX_HORN, MESSAGE_LENGTH);
                break;
            case CODE_RX_ALARM :
                rfTx.send(CODE_TX_ALARM, MESSAGE_LENGTH);
                break;
            case CODE_RX_LIGHT :
                rfTx.send(CODE_TX_LIGHT, MESSAGE_LENGTH);
                break;
            case CODE_RX_STOP :
                rfTx.send(CODE_TX_STOP, MESSAGE_LENGTH);
                delay(DELAY_TIME);
                rfTx.send(CODE_TX_STOP, MESSAGE_LENGTH);
                break;
        }
    }
}
