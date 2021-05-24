/****
 *  By kahoot_offline team 10/1/2020
 *  File này nạp cho node sử dụng esp8266
****/


#include "node_lib/node_lib.h"
#include "light_sleep/light_sleep.h"
void callback(){
    delay(500);
    Serial.printf("PIN D6: %d\r\n",digitalRead(D6));
    Serial.printf("PIN D7: %d\r\n",digitalRead(D7));

}
void setup()
{
    Serial.begin(115200);
    pinMode(D6,INPUT_PULLUP);
    pinMode(D7,INPUT_PULLUP);
    Light_sleep_helper::LightSleep.set_wake_up_pin(D5);
    // Light_sleep_helper::LightSleep.set_wakeup_callback(callback);
}

void loop()
{
    Serial.println("enter LightSleepEEEE");
    delay(100);
    Light_sleep_helper::LightSleep.light_sleep();
    callback();
    delay(100);
    Serial.print("Exit LightSleep: ");
    Serial.println(flags.error,DEC);
}
