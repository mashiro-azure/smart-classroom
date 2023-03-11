#pragma once

// wifi
// ESP32 cannot see 5G networks?
const char *WIFI_SSID = "98863005";
const char *WIFI_PASSWORD = "98863005";

// ir
uint16_t IRsendPin = 16; // GPIO pin numbers

// mqtt
IPAddress MQTT_BROKER(10, 69, 42, 69);
const uint16_t MQTT_BROKER_PORT = 1883;
const char *MQTT_POWER_TOPIC = "hass/ac/power";
const char *MQTT_AVAIL_TOPIC = "hass/ac/avail";
const char *MQTT_TEMP_LISTEN_TOPIC = "hass/ac/temp/listen";
const char *MQTT_TEMP_CONTROL_TOPIC = "hass/ac/temp/control";

// DHT
uint8_t DHTPin = 26;
uint8_t DHTType = DHT11;
const long DHTReadInterval = 1000; // in milliseconds
const char *DHT_TEMP_TOPIC = "dht/temp";
const char *DHT_TEMP_AVAIL_TOPIC = "dht/temp/avail";
const char *DHT_HUMID_TOPIC = "dht/humid";
const char *DHT_HUMID_AVAIL_TOPIC = "dht/humid/avail";

// CO2 Sensor
uint8_t CCS811pin = 23;
const char *CCS811_CO2_TOPIC = "ccs811/co2";
const char *CCS811_CO2_AVAIL_TOPIC = "ccs811/co2/avail";
const char *CCS811_ETVOC_TOPIC = "ccs811/etvoc";
const char *CCS811_ETVOC_AVAIL_TOPIC = "ccs811/etvoc/avail";

