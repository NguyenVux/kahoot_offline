#ifndef _BEACON_
#define _BEACON_
#include "Header.h"

namespace beacon
{
    extern Task task;

    void init(unsigned long interval,
              Scheduler *,
              esp_now_peer_info_t *,
              uint8_t *data, size_t len);
    void emit();
    bool onEnable();
    void onDisable();
} // namespace beacon
#endif