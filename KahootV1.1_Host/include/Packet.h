#ifndef _PACKET_
#define _PACKET_
#include "Header.h"
// ----------------------------------------
// This file defines the protocol to communicate between host (ESP-32) and client (ESP-8266)
// ----------------------------------------
enum packet_t : uint8_t
{
    BEACON = 0,
    REQ_ADDR,
    RECV_ANSW,
    RESPOND_ANSW,
};

// Act as a header
struct BasePacket
{
    const packet_t type;
    BasePacket(packet_t type) : type(type) {}
};

// Unicast/Broadcast host address with password
struct BeaconPacket : BasePacket
{
    int password;
    BeaconPacket(int password) : BasePacket(packet_t::BEACON), password(password) {}
};

// If for some reason the BeaconPacket 
struct RequestBeaconPacket : BasePacket
{
    int password;
    RequestBeaconPacket(int password) : BasePacket(packet_t::REQ_ADDR), password(password) {}
};

// Host receive this from client(s)
struct BtnPacket : BasePacket
{
    uint8_t button;
    BtnPacket(uint8_t button) : BasePacket(packet_t::RECV_ANSW), button(button) {}
};

// Broadcast correct answer to client(s)
struct AnswPacket : BasePacket
{
    uint8_t answer;
    AnswPacket(uint8_t answer) : BasePacket(packet_t::RESPOND_ANSW), answer(answer) {}
};
#endif // !_PACKET_