#include "Beacon.h"
namespace beacon
{
    Task task;
    esp_now_peer_info_t *peer;
    uint8_t *data;
    size_t len;
    void init(unsigned long interval,
              Scheduler *scheduler,
              esp_now_peer_info_t *peer_info,
              uint8_t *data, size_t len)
    {
        peer = peer_info;
        task.set(interval, TASK_FOREVER, emit, onEnable, onDisable);

        beacon::data = data;
        beacon::len = len;

        scheduler->addTask(task);
    }

    void emit()
    {
        esp_err_t err = esp_now_send(peer->peer_addr, data, len);
    }

    bool onEnable()
    {
        esp_err_t err = esp_now_add_peer(peer);
        return err == ESP_OK || err == ESP_ERR_ESPNOW_EXIST;
    }

    void onDisable()
    {
        esp_now_del_peer(peer->peer_addr);
    }
} // namespace beacon
