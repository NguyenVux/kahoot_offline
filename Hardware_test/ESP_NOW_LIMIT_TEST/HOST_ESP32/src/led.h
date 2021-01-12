#include <Arduino.h>

class Led
{
public:
    enum mode
    {
        OFF,
        ON,
        BLINK,
    };
    Led(uint8_t pin);
    void setPin(uint8_t);
    
    void on();
    void off();
    void blink(unsigned long interval);
    /*
    @brief Should not call in loop(). After quickBlink, LED returns to previous mode
    @param time     how many times led blink
    @param interval on time and off time
    */
    void quickBlink(uint8_t time, unsigned long interval);

    void update();

    mode getMode() const;
    uint8_t getPin() const;
    unsigned long getInterval() const;

private:
    uint8_t pin;
    mode ledMode = mode::OFF;
    // Three variables below are used for blink, quick_blink
    bool state = false;
    unsigned long interval = 0;
    unsigned long prevMillis = 0;
    // Three variables below are used for quick_blink
    unsigned long prevInterval = 0;
    uint8_t quickBlinkCounter = 0;
    uint8_t quickBlinkTime = 0;
    void (Led::*modeFunc)() = NULL;
    void blinkUpdate();
    void quickBlinkUpdate();
};