# Smart Classroom

**Not for public use.**

 This repo is meant for internal testing only. Those who know, know.

## Dependencies
These libraries can be installed through Arduino's Library Manager.
- IRremoteESP8266
- PubSubClient

## Quick Testing
1. Install `Mosquitto` from [mosquitto](https://mosquitto.org) or from your distro's repo.
1. Clone this repo, **do not change the structure of the folder**.
1. In `include/settings.h`, modify `WIFI_SSID`, `WIFI_PASSWORD`, `MQTT_BROKER` and `MQTT_BROKER_PORT` if neccessary.
1. Upload the `esp32_mqtt_client.ino` sketch to your ESP32.
1. Use `mosquitto_pub -r -t hass/ac/temp/control -m "25.0"` to send commands to ESP32, this should trigger a temperature changing IR event.
    - `-r`, this sets the RETAIN flag, optional.
    - `-m`, this sets the message, ranging from 18.0-26.0, **required**.
1. Optionally, subscribing to topic `hass/ac/temp/listen` can be used to check if ESP32 has correctly responded.
