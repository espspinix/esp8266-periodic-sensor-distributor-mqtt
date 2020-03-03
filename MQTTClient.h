#include <PubSubClient.h>
#include <ESP8266WiFi.h>

#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H 1

class MQTTClient {
  protected:
  static WiFiClient espClient;
  static PubSubClient client;
  static const int reconnectWait;
  static const char* MQTT_BROKER;
  static const char* MQTT_CLIENTID;

  public:
  static int publish(const char * address, const char * value);
  static int initialized;
  static int activated;
  static int connected;
  static void setupMQTT();
  static void activate();
  static int reconnectMQTT();
};

#endif
