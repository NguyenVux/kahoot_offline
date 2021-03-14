#include <State.h>

StateBase *State::getState(state_t state)
{
    return stateContainer[state];
}

StateBase *State::newState(state_t state)
{
    // return stateContainer[state] = 
}