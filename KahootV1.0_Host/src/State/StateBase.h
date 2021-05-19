#ifndef _STATE_BASE_
#define _STATE_BASE_
#include <Arduino.h>

enum state_t
{
    Idle,
    Pairing,
};

class StateBase
{
public:
    /*
        Initialize the state, with data from Serial if needed.
    */
    virtual bool init(HardwareSerial& = Serial);
    virtual bool initDefault();
    virtual void loop();
    virtual void clone(StateBase *);
};
#endif
