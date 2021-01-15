#ifndef _CLIENT_
#define _CLIENT_
#include <Arduino.h>
#include "util.h"
struct clientInfo_t
{
    uint8_t macAddr[6];
    uint8_t id = 0;
};
#define CLIENT_LIMIT 100
namespace client
{
    void add(const uint8_t *macAddr, uint8_t id);
    size_t size();
    clientInfo_t *get(size_t);
    clientInfo_t *search(const uint8_t *macAddr);
    clientInfo_t *search(uint8_t id);
} // namespace client
#endif