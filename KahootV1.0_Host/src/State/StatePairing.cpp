#include <./State/StatePairing.h>

bool StatePairing::init(HardwareSerial &serial)
{
    return (parse(data, serial)) ? addPeer() : false;
}

bool StatePairing::initDefault()
{
    data.interval = DEFAULT_INTERVAL;
    memcpy(data.peer_addr, broadcastMAC, 6);

    return addPeer();
}

void StatePairing::loop()
{
}

void StatePairing::clone(StateBase *addr)
{
    StatePairing state;
    memcpy(addr, &state, sizeof(state));
}

bool StatePairing::addPeer()
{
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, data.peer_addr, 6);
    peerInfo.channel = DEFAULT_CHANNEL;
    peerInfo.encrypt = false; //ESP8266 cannot read encrypted messages

    esp_err_t err = esp_now_add_peer(&peerInfo);

    switch (err)
    {
    case ESP_OK:
        return true;
    case ESP_ERR_ESPNOW_FULL:
        Serial.println("[ERROR] Peer list is full");
        return false;
    case ESP_ERR_ESPNOW_EXIST:
        Serial.print("[ERROR] Peer has existed");
        serialPrintMAC(peerInfo.peer_addr);
        return false;
    default:
        return false;
    }
}