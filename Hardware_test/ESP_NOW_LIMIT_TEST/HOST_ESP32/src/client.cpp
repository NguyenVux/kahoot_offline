#include "client.h"
size_t size = 0;
clientInfo_t clientInfo[CLIENT_LIMIT];
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

clientInfo_t *ClientInfo()
{
    return clientInfo;
}

