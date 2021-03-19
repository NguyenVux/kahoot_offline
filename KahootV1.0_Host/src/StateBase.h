#ifndef _STATE_BASE_
#define _STATE_BASE_
#include <Arduino.h>
class StateBase
{
public:
    virtual bool init(HardwareSerial& = Serial);
    virtual void loop();
    virtual void clone(StateBase *);
};

class State
{
public:
    enum state_t
    {
        Idle,
        Pairing,
    };
    state_t getCurStateName() const;
    StateBase *getCurState();
    StateBase *operator->();
    StateBase *setCurState(state_t);
    void resetCurState();

private:
    state_t curState = Idle;
    state_t nextState;
};
#endif
