#ifndef _UTIL_
#define _UTIL_
#include <Arduino.h>

template <typename T>
bool cmpArr(
    const T *a, const T *b, size_t n1, size_t n2,
    bool (*cmp)(const T &, const T &) = [](const T &a, const T &b) { return a == b; })
{
    if (n1 != n2)
        return false;
    for (size_t i = 0; i < n1; ++i)
        if (!cmp(a[i], b[i]))
            return false;
    return true;
}

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