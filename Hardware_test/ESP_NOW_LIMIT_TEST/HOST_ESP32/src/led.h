#ifndef _LED_
#define _LED_
#include <Arduino.h>
#include "stopwatch.h"
class Led
{
public:
    enum mode
    {
        OFF = 0,
        ON = 1,
        BLINK,
    };
    Led(uint8_t pin);
    void setPin(uint8_t);
    
    void on();
    void off();
    void toggle();
    void blink(unsigned long interval);
    void blink(unsigned long interval, uint8_t blinkNum);
    //Call this in loop()
    void update();

    mode getMode() const;
    uint8_t getPin() const;

private:
    uint8_t pin;
    mode ledMode = mode::OFF;

    Stopwatch<> timer;
    unsigned long interval = 0;
    void (Led::*modeFunc)() = &Led::blinkUpdate;

    uint8_t quickBlinkCounter = 0;
    uint8_t quickBlinkTime = 0;

    void blinkUpdate();
    void quickBlinkUpdate();
};
#endif