#include "light_sleep.h"


Light_sleep_helper Light_sleep_helper::LightSleep;

void Light_sleep_helper::light_sleep()
{
    WiFi.mode(WIFI_OFF);
    gpio_pin_wakeup_enable(GPIO_ID_PIN(_wake_up_pin), GPIO_INT_TYPE::GPIO_PIN_INTR_LOLEVEL);
    wifi_set_opmode(NULL_MODE);
    wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
    wifi_fpm_open();
    if(!_callback)  wifi_fpm_set_wakeup_cb(_callback);
    wifi_fpm_do_sleep(FPM_SLEEP_MAX_TIME);
}

void Light_sleep_helper::set_wake_up_pin(const uint8_t& wake_up_pin)
{
    _wake_up_pin = wake_up_pin;
    pinMode(_wake_up_pin, INPUT_PULLUP);
}
void Light_sleep_helper::set_wakeup_callback(fpm_wakeup_cb cb)
{
    _callback = cb;
}
