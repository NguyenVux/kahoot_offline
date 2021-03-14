#ifndef _STATE_BASE_
#define _STATE_BASE_
#include <Arduino.h>
class StateBase
{
public:
    virtual void init(void* param = nullptr);
    
    virtual void loop();
};
#endif
