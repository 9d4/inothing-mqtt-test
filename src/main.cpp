#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define WIFI_SSID "kucinghome"
#define WIFI_PASS "123456789"

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

const char *MQTT_HOST = "194.164.40.4";
const uint16 MQTT_PORT = 1883;
const char *MQTT_USER = "user0";
const char *MQTT_PASS = "user0";

void cb(const char topic[], byte *payload, unsigned int length)
{
    Serial.println(topic);
    Serial.println(length);
}

void setup()
{
    Serial.begin(115200);

    WiFi.setHostname("ESP ON TESTING");
    WiFi.setAutoConnect(true);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    WiFi.printDiag(Serial);

    mqtt.setCallback(cb);
    mqtt.setServer(MQTT_HOST, MQTT_PORT);
    mqtt.connect("esp", MQTT_USER, MQTT_PASS);
    mqtt.subscribe("user0@a1f2f3b40c1d/air/temp");
}

void reconnectMqtt()
{
    while (!mqtt.connected())
    {
        Serial.println("Attempting connect to mqtt server");
        mqtt.connect("esp", MQTT_USER, MQTT_PASS);
        delay(1000);
        mqtt.subscribe("user0@a1f2f3b40c1d/air/temp");
    }

    Serial.println("Connected");
}

void loop()
{
    delay(1000);
    mqtt.loop();
    if (mqtt.connected() == false)
    {
        reconnectMqtt();
    }
}
