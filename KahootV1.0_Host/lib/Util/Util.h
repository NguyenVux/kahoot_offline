#ifndef _UTIL_
#define _UTIL_
#include <Arduino.h>
void serialPrintMAC(const uint8_t *addr)
{
    char str[18];
    snprintf(str, sizeof(str), MACSTR,
             MAC2STR(addr));
    Serial.print(str);
}

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
#endif