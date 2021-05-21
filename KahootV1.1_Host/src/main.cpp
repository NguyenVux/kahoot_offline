#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#define _DEBUG_
#define _BTSERIAL_
#include <SerialLog.h>
// Only one file is allowed to include TaskScheduler
#define _TASK_STATUS_REQUEST
#include "TaskScheduler.h"

#include "Beacon.h"
#include "Packet.h"

int generatePassword();
void onRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len);

esp_now_peer_info_t broadcastPeer{{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
Scheduler scheduler;
BeaconPacket broadcastData(generatePassword());

void setup()
{
  Serial.begin(115200);
#ifdef _BTSERIAL_
  SerialBT.begin("ESP32-LOG");
#endif

  broadcastPeer.channel = 0;
  broadcastPeer.encrypt = false;

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK)
  {
    PRINTLN("[ERROR] Initialize ESP-NOW failed");
    return;
  }

  esp_now_register_recv_cb(&onRecv);

  unsigned long broadcast_interval = 1000 * TASK_MILLISECOND;
  PRINTF("[INFO] Password: %d", broadcastData.password);
  beacon::init(broadcast_interval, &scheduler, &broadcastPeer, (uint8_t *)&broadcastData, sizeof(broadcastData));

  beacon::task.enable();
}

void loop()
{
  scheduler.execute();
  PRINTLN("bluetooth");
}

// Generate 4 digits password
int generatePassword()
{
  randomSeed(analogRead(0));
  int password = 0;
  for (int i = 1; i <= 4; i++)
    password += random(1, 5) * i; // Only generate 1 to 4
  return password;
}

void onRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
  // Unpack data
  switch (((BasePacket *)data)->type)
  {
  case packet_t::RECV_ANSW:
    /* code */
    break;
  default:
    break;
  }
}