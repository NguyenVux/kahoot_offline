#ifndef _CLIENT_
#define _CLIENT_
#include <Arduino.h>
struct clientInfo_t
{
    uint8_t macAddr[6];
    uint8_t id = 0;
};
#define CLIENT_LIMIT 100

void addClient(const uint8_t *macAddr, uint8_t id);
size_t clientSize();
clientInfo_t *ClientInfo();
#endif