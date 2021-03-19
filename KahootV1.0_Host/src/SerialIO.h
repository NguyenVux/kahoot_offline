#ifndef _SERIAL_IO_
#define _SERIAL_IO_
#include <header.h>

struct SerialHeader{
    State::state_t changeState;
    bool resetState;
};

bool parseHeader(SerialHeader &header, HardwareSerial &serial = Serial);

template <typename T>
bool parse(T& obj, HardwareSerial& serial = Serial)
{
    return serial.readBytes((uint8_t *)&obj, sizeof(obj)) == sizeof(obj);
}
#endif