#include <StateBase.h>
#include <StatePairing.h>

StateBase *stateContainer[] = {
    new StateBase(),
    new StatePairing(),
};

bool StateBase::init(HardwareSerial &) { return true; }

void StateBase::loop() {}

void StateBase::clone(StateBase *) {}

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

void State::resetCurState()
{
    stateContainer[curState]->clone(stateContainer[curState]);
}
