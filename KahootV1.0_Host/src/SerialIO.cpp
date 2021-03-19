#include <SerialIO.h>

bool parseHeader(SerialHeader& header, HardwareSerial &serial)
{
    return serial.readBytes((char *)&header, sizeof(header)) == sizeof(header);
}