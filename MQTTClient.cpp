#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "MQTTClient.h"

int MQTTClient::initialized = false;
int MQTTClient::activated = false;
int MQTTClient::connected = false;
const int MQTTClient::reconnectWait = 200;
const char* MQTTClient::MQTT_BROKER = "192.168.188.33";
const char* MQTTClient::MQTT_CLIENTID = "LIVING_ESP";

WiFiClient MQTTClient::espClient = WiFiClient();
PubSubClient MQTTClient::client = PubSubClient(MQTTClient::espClient);

void MQTTClient::activate() {
  activated = true;
  setupMQTT();
}

int MQTTClient::publish(const char * address, const char * value) {
  if (initialized == false) return false;
  if (!reconnectMQTT()) return false;

  #ifdef DEBUG
  Serial.print("Publishing '");
  Serial.print(value);
  Serial.print("' to '");
  Serial.println(address);
  #endif

  client.publish(address, value, true);
  return true;
}

void MQTTClient::setupMQTT() {
  Serial.println("Setting up MQTTClient..");
  client.setServer(MQTT_BROKER, 1883);

  Serial.println("Connecting to broker..");
  if (client.connect(MQTT_CLIENTID)) {
    Serial.println("MQTTClient Connected!");
    connected = true;
  }

  Serial.println("MQTTClient initialized!");
  initialized = true;
}

int MQTTClient::reconnectMQTT() {
  if (!client.connected()) {
    Serial.print("Reconnecting to MQTT broker...");
    if (!client.connect(MQTT_CLIENTID)) {
      Serial.print("failed, rc=");
      Serial.println(client.state());

      return false;
    }
    Serial.println("done!");
  }
  return true;
}
