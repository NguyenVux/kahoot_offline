/****
 *  By kahoot_offline team 10/1/2020
 *  File này nạp cho node sử dụng esp8266
****/


#include "node_lib/node_lib.h"
#include "light_sleep/light_sleep.h"
void setup()
{
    Serial.begin(115200);
    Light_sleep_helper::LightSleep.set_wake_up_pin(D5);
    
}

void loop()
{
    Serial.println("enter LightSleepEEEE");
    delay(100);
    Light_sleep_helper::LightSleep.light_sleep();
    delay(100);
    Serial.print("Exit LightSleep: ");
    Serial.println(flags.error,DEC);
    delay(3000);
}
