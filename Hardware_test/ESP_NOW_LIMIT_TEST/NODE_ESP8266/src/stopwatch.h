#ifndef _STOPWATCH_
#define _STOPWATCH_
#include <Arduino.h>
template <unsigned long (*time_func)() = millis>
class Stopwatch
{
public:
    unsigned long start()
    {
        return startTime = time_func();
    }
    unsigned long elapsed()
    {
        return time_func() - startTime;
    }

private:
    unsigned long startTime = 0;
};
#endif