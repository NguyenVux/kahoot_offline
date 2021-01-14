#include "client.h"

clientInfo_t clientInfo[CLIENT_LIMIT];
size_t size = 0;

void addClient(const uint8_t *macAddr, uint8_t id)
{
    if (size < CLIENT_LIMIT)
    {
        memcpy(clientInfo[size].macAddr, macAddr, 6);
        clientInfo[size].id = id;
        ++size;
    }
}

size_t clientSize()
{
    return size;
}