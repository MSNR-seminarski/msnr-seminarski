/* -----------------------------------------------------------------------------
 *      pin 10 -> DATA
 *      +5V    -> VCC
 *      GND    -> GND
-------------------------------------------------------------------------------- */

#include <RCSwitch.h>

#define CODE_TX_LEFT        0b11000001
#define CODE_TX_RIGHT       0b11000011
#define CODE_TX_FORWARD     0b11000111
#define CODE_TX_BACKWARD    0b11001111
#define CODE_TX_LIGHT       0b11010001
#define CODE_TX_HORN        0b11011001
#define CODE_TX_ALARM       0b11011101
#define CODE_TX_STOP        0b11011111
#define CODE_TX_STOP_HORN   0b11100101
#define CODE_TX_STOP_LIGHT  0b11101010
#define CODE_TX_STOP_ALARM  0b11101001

#define CODE_RX_LEFT        1
#define CODE_RX_STOP        5
#define CODE_RX_RIGHT       2
#define CODE_RX_FORWARD     3
#define CODE_RX_BACKWARD    4
#define CODE_RX_HORN        6
#define CODE_RX_ALARM       7
#define CODE_RX_LIGHT       8
#define CODE_RX_STOP_LIGHT  13
#define CODE_RX_STOP_ALARM  12
#define CODE_RX_STOP_HORN   11

#define MESSAGE_LENGTH      8
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
    static int receivedData;

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
            case CODE_RX_STOP_LIGHT :
                rfTx.send(CODE_TX_STOP_LIGHT, MESSAGE_LENGTH);
                break;
            case CODE_RX_STOP_ALARM :
                rfTx.send(CODE_TX_STOP_ALARM, MESSAGE_LENGTH);
                break;
            case CODE_RX_STOP_HORN :
                rfTx.send(CODE_TX_STOP_HORN, MESSAGE_LENGTH);
                break;
            case CODE_RX_STOP :
                rfTx.send(CODE_TX_STOP, MESSAGE_LENGTH);
                delay(1);
                rfTx.send(CODE_TX_STOP, MESSAGE_LENGTH);
                break;
        }
    }
}
