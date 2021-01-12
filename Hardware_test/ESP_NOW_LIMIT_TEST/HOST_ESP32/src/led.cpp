#include "led.h"
Led::Led(uint8_t pin)
    : pin(pin)
{
    pinMode(pin, OUTPUT);
};

Led::mode Led::getMode() const
{
    return ledMode;
}

void Led::setPin(uint8_t ledPin)
{
    pin = ledPin;
}

uint8_t Led::getPin() const
{
    return pin;
}

unsigned long Led::getInterval() const
{
    return interval;
}

void Led::on()
{
    this->ledMode = ledMode;
    digitalWrite(pin, HIGH);
    modeFunc = NULL;
}

void Led::off()
{
    this->ledMode = ledMode;
    digitalWrite(pin, LOW);
    modeFunc = NULL;
}

void Led::blink(unsigned long mili)
{
    this->ledMode = ledMode;
    interval = mili;
    modeFunc = &Led::blinkUpdate;
}

void Led::quickBlink(uint8_t time, unsigned long mili)
{
    quickBlinkCounter = 0;
    //Off time also counted
    quickBlinkTime = time * 2;
    interval = mili;
    prevInterval = interval;
    modeFunc = &Led::quickBlinkUpdate;
}

void Led::update()
{
    if (modeFunc != NULL)
        (this->*modeFunc)();
}

void Led::blinkUpdate()
{
    unsigned long curMillis = millis();
    if (curMillis - prevMillis >= interval)
    {
        prevMillis = curMillis;
        state = !state;
        digitalWrite(pin, state);
    }
}

void Led::quickBlinkUpdate()
{
    if (quickBlinkCounter < quickBlinkTime)
    {
        unsigned long curMillis = millis();
        if (curMillis - prevMillis >= interval)
        {
            ++quickBlinkCounter;
            prevMillis = curMillis;
            state = !state;
            digitalWrite(pin, state);
        }
    }
    else //restore previous mode
    {
        switch (ledMode)
        {
        case OFF:
            off();
            break;
        case ON:
            on();
            break;
        case BLINK:
            blink(interval);
            break;
        default:
            break;
        }
    }
}