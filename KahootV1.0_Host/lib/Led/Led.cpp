#include "led.h"
Led::Led(uint8_t pin)
    : pin(pin)
{
    pinMode(pin, OUTPUT);
};

void Led::setPin(uint8_t ledPin)
{
    pin = ledPin;
}

void Led::on()
{
    ledMode = ON;
    digitalWrite(pin, HIGH);
}

void Led::off()
{
    ledMode = OFF;
    digitalWrite(pin, LOW);
}

void Led::toggle()
{
    ledMode = (Led::mode)!digitalRead(pin);
    digitalWrite(pin, ledMode);
}

Led::mode Led::getMode() const
{
    return ledMode;
}

uint8_t Led::getPin() const
{
    return pin;
}

void Led::blink(unsigned long mili)
{
    ledMode = BLINK;
    interval = mili;
    modeFunc = &Led::blinkUpdate;
}

void Led::blink(unsigned long mili, uint8_t blinkNum)
{
    quickBlinkCounter = 0;
    //Off time also counted
    quickBlinkTime = blinkNum * 2;
    interval = mili;
    modeFunc = &Led::quickBlinkUpdate;
}

//Call this in loop()
void Led::update()
{
    if (ledMode == BLINK)
        (this->*modeFunc)();
}

void Led::blinkUpdate()
{
    if (timer.elapsed() >= interval)
    {
        timer.start();
        digitalWrite(pin, !digitalRead(pin));
    }
}

void Led::quickBlinkUpdate()
{
    if (quickBlinkCounter < quickBlinkTime && timer.elapsed() >= interval)
    {
        timer.start();
        digitalWrite(pin, !digitalRead(pin));
        ++quickBlinkCounter;
    }
}