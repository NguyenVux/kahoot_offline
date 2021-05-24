#include "node_lib.h"


void initSystem()
{
    flags.error = SYS_INIT;
}

bool load_from_EEPROM()
{
    EEPROM.begin(6);
    EEPROM.get(0,Host_address);
    EEPROM.end();
    for(uint8_t i =0; i < 6;i++)
    {
        if(Host_address.addr[i] != 0xff)
        {
            return true;
        }
    }
    return false;
}