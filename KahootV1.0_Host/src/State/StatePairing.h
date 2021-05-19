#ifndef _STATE_PAIRING_
#define _STATE_PAIRING_
#include <header.h>
#include <SerialIO.h>
#include <./State/StateBase.h>

#define DEFAULT_INTERVAL 1000

const uint8_t broadcastMAC[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

class StatePairing : public StateBase
{
public:
    bool init(HardwareSerial& = Serial);
    bool initDefault();
    void loop();
    void clone(StateBase *);

    bool addPeer();

private:
    struct Data
    {
        size_t interval;
        uint8_t peer_addr[6];
    } data;
};
#endif