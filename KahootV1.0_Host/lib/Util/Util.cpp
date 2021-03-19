#include <Util.h>

void serialPrintMAC(const uint8_t *addr)
{
    char str[18];
    snprintf(str, sizeof(str), MACSTR,
             MAC2STR(addr));
    Serial.print(str);
}