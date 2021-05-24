#include <Arduino.h>
#include <EEPROM.h>

enum error_code
{
    NORMAL = 0b00000000,
    SYS_INIT = 0b00000001,
    EEPROM_LOAD = 0b00000010,
    ESPNOW = 0b00000100
};

enum Mode
{
    PAIR,
    RUN
};

struct
{
    error_code error = NORMAL;
    Mode running_mode = RUN;
} flags;



struct
{
    uint8_t addr[6];
} Host_address;

void initSystem();
bool load_from_EEPROM();
void pair();
void run();