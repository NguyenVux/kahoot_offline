#include <./State/StateBase.h>

bool StateBase::init(HardwareSerial &) { return true; }

bool StateBase::initDefault() { return true; }

void StateBase::loop() {}

void StateBase::clone(StateBase *) {}