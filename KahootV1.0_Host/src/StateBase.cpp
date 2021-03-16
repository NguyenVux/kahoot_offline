#include <StateBase.h>

StateBase *stateContainer[] = {
    new StateBase(),
};

void StateBase::init(void *param) {}

void StateBase::loop() {}

void StateBase::clone(StateBase *ptr) {}

State::state_t State::getCurStateName() const
{
    return curState;
}

StateBase *State::getCurState()
{
    return stateContainer[curState];
}

StateBase *State::operator->()
{
    return getCurState();
}

StateBase *State::setCurState(state_t state)
{
    curState = state;
    return getCurState();
}
