#include <StatePairing.h>

bool StatePairing::init(HardwareSerial &serial)
{
    if (!parse(data, serial))
    {
        //Fallback
        data.interval = DEFAULT_INTERVAL;
        memcpy(data.peer_addr, broadcastMAC, 6);
    }

    if (!esp_now_is_peer_exist(data.peer_addr))
    {
        esp_now_peer_info_t peerInfo;
        memcpy(peerInfo.peer_addr, data.peer_addr, 6);
        peerInfo.channel = DEFAULT_CHANNEL;
        peerInfo.encrypt = false;

        if (esp_now_add_peer(&peerInfo) != ESP_OK)
        {
            Serial.println("Failed to add peer");
            return false;
        }
    }

    return true;
}

void StatePairing::loop()
{

}

void StatePairing::clone(StateBase *addr)
{
    *addr = StatePairing();
}