#ifndef _STATE_
#define _STATE_

#include <./State/StateBase.h>
#include <./State/StatePairing.h>

// StateBase *stateContainer[] = {
//     new StateBase(),
//     new StatePairing(),
// };

class State
{
public:
    state_t getCurStateName() const;
    StateBase *getCurState();
    StateBase *operator->();
    StateBase *setCurState(state_t);
    void resetCurState();

private:
    union states
    {
        StateBase base;
        StatePairing pairing;
        states() { new (&base) StateBase(); }
    };
    state_t curStateName = Idle;
    StateBase *curState;
};

#endif