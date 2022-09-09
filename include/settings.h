#pragma once

// wifi
// ESP32 cannot see 5G networks?
const char* WIFI_SSID = "";
const char* WIFI_PASSWORD = "";

// ir
uint16_t IRsendPin = 16;     // GPIO pin numbers

// mqtt
IPAddress MQTT_BROKER(192,168,80,180);
const uint16_t MQTT_BROKER_PORT = 1883;
const char* MQTT_POWER_TOPIC = "hass/ac/power";
const char* MQTT_AVAIL_TOPIC = "hass/ac/avail";
const char* MQTT_TEMP_LISTEN_TOPIC = "hass/ac/temp/listen";
const char * MQTT_TEMP_CONTROL_TOPIC = "hass/ac/temp/control";
