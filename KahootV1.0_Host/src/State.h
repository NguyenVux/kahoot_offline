#ifndef _STATE_
#define _STATE_
#include <Arduino.h>
#include <StateBase.h>
class State
{
public:
    enum state_t
    {
        Broadcast,
    };
    StateBase *getState(state_t);
    StateBase *newState(state_t);

private:
    StateBase *stateContainer[] = {};
};
#endif
