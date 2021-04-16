/****
 *  By kahoot_offline team 10/1/2020
 *  File này nạp cho node sử dụng esp8266
****/


#include "node_lib.h"
void setup()
{
    InitSys();
}

void loop()
{
    if(mode == PAIRING)
    {
        PairMode();
        flags = false;
    }
    else if (flags)
    { 
        delay(10);
        check();
        setInterrupt();
        flags = false;
    }

    
    //delay(500);
    
}
