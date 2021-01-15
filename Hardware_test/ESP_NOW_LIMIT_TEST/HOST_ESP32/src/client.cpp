#include "client.h"
size_t clientSize = 0;
clientInfo_t clientInfo[CLIENT_LIMIT];
void client::add(const uint8_t *macAddr, uint8_t id)
{
    if (clientSize < CLIENT_LIMIT)
    {
        memcpy(clientInfo[clientSize].macAddr, macAddr, 6);
        clientInfo[clientSize].id = id;
        ++clientSize;
    }
}

size_t client::size()
{
    return clientSize;
}

clientInfo_t *client::get(size_t idx)
{
    return &clientInfo[idx];
}

clientInfo_t *search(const uint8_t *macAddr)
{
    for (int i = 0; i < clientSize; ++i)
    {
        if (cmpArr(clientInfo[i].macAddr, macAddr, 6, 6))
            return &clientInfo[i];
    }
    return NULL;
}
clientInfo_t *search(uint8_t id)
{
    for (int i = 0; i < clientSize; ++i)
    {
        if (clientInfo[i].id == id)
            return &clientInfo[i];
    }
    return NULL;
}
