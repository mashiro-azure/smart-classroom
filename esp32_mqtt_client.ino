// https://github.com/knolleary/pubsubclient/blob/master/examples/mqtt_esp8266/mqtt_esp8266.ino
// https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html

// If using DeptEng-NGX6, check same subnet as Home Assistant.

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <IRsend.h>
#include "include/settings.h"
#include "include/acData.h"

// setup wifi & mqtt
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// setup ir
IRsend IRsender(IRsendPin);

void setup_wifi()
{
    delay(3);
    WiFi.mode(WIFI_STA);
    Serial.println();
    Serial.print(F("Connecting to "));
    Serial.println(WIFI_SSID);

    // connect to wifi, retry indefinitely if fail.
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int wifiConnectTries = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(3000);
        Serial.print(".");
        if (wifiConnectTries >= 10)
        {
            Serial.print(F("Wifi not connecting, resetting..."));
            ESP.restart();
        }
        else
        {
            wifiConnectTries += 1;
        }
    }

    Serial.println();
    Serial.print(F("Connected with IP: "));
    Serial.println(WiFi.localIP());
}

void mqttReconnect()
{
    while (!mqttClient.connected())
    {
        // generate mqtt client ID for clients.
        String clientID = "ESP32Client-";
        clientID += String(random(0xffff), HEX);

        Serial.print(clientID);
        Serial.println(F(" - Establishing MQTT connection to broker..."));

        // connected to mqtt broker
        if (mqttClient.connect(clientID.c_str()))
        {
            // announce going online
            mqttClient.publish(MQTT_AVAIL_TOPIC, "online", true);
            // listen to power topic
            mqttClient.subscribe(MQTT_POWER_TOPIC);
            mqttClient.subscribe(MQTT_TEMP_CONTROL_TOPIC);
            Serial.print(F("Connected. Listening to topic: "));
            Serial.println(MQTT_POWER_TOPIC);
        }
        // not conencted to mqtt broker, retry
        else
        {
            Serial.print(F("MQTT connection failed. state: "));
            Serial.println(mqttClient.state());
            delay(3000);
        }
    }
}

// Perform actions when mqtt receive payload from topic.
void callback(char *topic, byte *payload, uint length)
{
    Serial.print(F("Message arrived on topic ["));
    Serial.print(topic);
    Serial.print(F("] - "));

    // format payload
    payload[length] = '\0';
    Serial.println((char *)payload);

    // TODO: implement different laser firing, by (strncmp(char*) topic, TOPIC, length)

    // TODO: replace this with switch
    if (strncmp((char *)topic, "hass/ac/temp/control", length) == 0)
    {
        if (strncmp((char *)payload, "18.0", length) == 0)
        {
            Serial.println("Action - Temp - 18");
            IRsender.sendRaw(AC18, sizeof(AC18) / sizeof(AC18[0]), 38);
            mqttClient.publish(MQTT_TEMP_LISTEN_TOPIC, "18.0", true);
        }
        if (strncmp((char *)payload, "19.0", length) == 0)
        {
            Serial.println("Action - Temp - 19");
            IRsender.sendRaw(AC19, sizeof(AC19) / sizeof(AC19[0]), 38);
            mqttClient.publish(MQTT_TEMP_LISTEN_TOPIC, "19.0", true);
        }
        if (strncmp((char *)payload, "20.0", length) == 0)
        {
            Serial.println("Action - Temp - 20");
            IRsender.sendRaw(AC20, sizeof(AC20) / sizeof(AC20[0]), 38);
            mqttClient.publish(MQTT_TEMP_LISTEN_TOPIC, "20.0", true);
        }
        if (strncmp((char *)payload, "21.0", length) == 0)
        {
            Serial.println("Action - Temp - 21");
            IRsender.sendRaw(AC21, sizeof(AC21) / sizeof(AC21[0]), 38);
            mqttClient.publish(MQTT_TEMP_LISTEN_TOPIC, "21.0", true);
        }
        if (strncmp((char *)payload, "22.0", length) == 0)
        {
            Serial.println("Action - Temp - 22");
            IRsender.sendRaw(AC22, sizeof(AC22) / sizeof(AC22[0]), 38);
            mqttClient.publish(MQTT_TEMP_LISTEN_TOPIC, "22.0", true);
        }
        if (strncmp((char *)payload, "23.0", length) == 0)
        {
            Serial.println("Action - Temp - 23");
            IRsender.sendRaw(AC23, sizeof(AC23) / sizeof(AC23[0]), 38);
            mqttClient.publish(MQTT_TEMP_LISTEN_TOPIC, "23.0", true);
        }
        if (strncmp((char *)payload, "24.0", length) == 0)
        {
            Serial.println("Action - Temp - 24");
            IRsender.sendRaw(AC24, sizeof(AC24) / sizeof(AC24[0]), 38);
            mqttClient.publish(MQTT_TEMP_LISTEN_TOPIC, "24.0", true);
        }
        if (strncmp((char *)payload, "25.0", length) == 0)
        {
            Serial.println("Action - Temp - 25");
            IRsender.sendRaw(AC25, sizeof(AC25) / sizeof(AC25[0]), 38);
            mqttClient.publish(MQTT_TEMP_LISTEN_TOPIC, "25.0", true);
        }
        if (strncmp((char *)payload, "26.0", length) == 0)
        {
            Serial.println("Action - Temp - 26");
            IRsender.sendRaw(AC26, sizeof(AC26) / sizeof(AC26[0]), 38);
            mqttClient.publish(MQTT_TEMP_LISTEN_TOPIC, "26.0", true);
        }
    }
    if (strncmp((char *)topic, "hass/ac/power", length) == 0)
    {
        if (strncmp((char *)payload, "ON", length) == 0)
        {
            Serial.println("Action - Power - ON");
            // IRsender.sendRaw(AC25, sizeof(AC25) / sizeof(AC25[0]), 38);
            // mqttClient.publish(MQTT_TEMP_LISTEN_TOPIC, "25.0", true);
        }
        if (strncmp((char *)payload, "OFF", length) == 0)
        {
            Serial.println("Action - Power - OFF");
            IRsender.sendRaw(ACOFF, sizeof(ACOFF) / sizeof(ACOFF[0]), 38);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    // setup wifi
    setup_wifi();
    // setup mqtt
    //  TODO: use mDNS resolving if possible
    mqttClient.setServer(MQTT_BROKER, MQTT_BROKER_PORT);
    mqttClient.setCallback(callback);

    IRsender.begin();
}

void loop()
{
    if (!wifiClient.connected())
    {
        Serial.println(F("Wifi not connected."));
        setup_wifi();
    }

    if (!mqttClient.connected())
    {
        Serial.println(F("MQTT not connected."));
        mqttReconnect();
    }

    // keep alive MQTT.
    mqttClient.loop();
    delay(800); // to activate auto modem-sleep, hopefully
}
