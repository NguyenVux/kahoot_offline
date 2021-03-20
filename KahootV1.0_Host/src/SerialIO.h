#ifndef _SERIAL_IO_
#define _SERIAL_IO_
#include <header.h>

/*
    Since the Serial buffers only hold up to 64 bytes by default, the request message must shorter than 64 bytes.

    Data Code: a unique number to differentiate from normal logging.
    Header:
        changeState: A request to ESP32 to switch state
        resetState: if resetState is true, the state requested from changeState will reset itseft and call init()
    Body: extra information to initialize a new state. if resetState is false, this section has no effect.
    +-----------+---------+---------------+
    | Data Code |  Header |      Body     |
    +-----------+---------+---------------+
    |   1 byte  | 2 bytes | 0 to 60 bytes |
    +-----------+---------+---------------+
*/

struct SerialHeader
{
    State::state_t changeState;
    bool resetState;
};

bool parseHeader(SerialHeader &header, HardwareSerial &serial = Serial);

template <typename T>
bool parse(T &obj, HardwareSerial &serial = Serial)
{
    return serial.readBytes((uint8_t *)&obj, sizeof(obj)) == sizeof(obj);
}
#endif