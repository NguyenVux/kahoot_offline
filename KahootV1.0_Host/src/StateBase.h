#ifndef _STATE_BASE_
#define _STATE_BASE_
#include <Arduino.h>
class StateBase
{
public:
    virtual void init(void *param = nullptr);
    virtual void loop();
    virtual void clone(StateBase *);
};

class State
{
public:
    enum state_t
    {
        Idle,
        Broadcast,
    };
    state_t getCurStateName() const;
    StateBase *getCurState();
    StateBase *operator->();
    StateBase *setCurState(state_t);

private:
    state_t curState = Idle;
    state_t nextState;
};
#endif
