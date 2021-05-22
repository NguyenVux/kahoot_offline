#include <./State/State.h>

state_t State::getCurStateName() const
{
    return curStateName;
}

StateBase *State::getCurState()
{
    return NULL;
}

StateBase *State::operator->()
{
    return getCurState();
}

StateBase *State::setCurState(state_t state)
{
    curStateName = state;
    return getCurState();
}

void State::resetCurState()
{
    // stateContainer[curStateName]->clone(stateContainer[curState]);
}
