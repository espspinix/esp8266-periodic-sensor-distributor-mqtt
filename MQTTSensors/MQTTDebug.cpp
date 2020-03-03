#include "MQTTDebug.h"
#include "MQTTClient.h"
#include "StringUtilities.h"

const char* MQTTDebug::address = "/debug/";

int MQTTDebug::error(const char * sender, const char * message) {
  Serial.print("[ERROR] ");
  Serial.print(sender);
  Serial.print(":");
  Serial.println(message);

  return MQTTClient::publish(concatString(address, sender), message);
}

int MQTTDebug::info(const char * message) {
  Serial.print("[INFO] ");
  Serial.println(message);

  return MQTTClient::publish(concatString(address, "info"), message);
}
