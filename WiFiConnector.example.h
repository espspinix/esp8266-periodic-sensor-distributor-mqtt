#include <ESP8266WiFi.h>
#include "MQTTClient.h"
#include "MQTTDebug.h"
#include "StringUtilities.h"

#define USE_HOTSPOT TRUE

////////// WIFI
//system will first try to connect to hotspot for 6 seconds
#ifdef USE_HOTSPOT
const char* hotspot_ssid = "**YOUR HOTSPOT SSID**";
const char* hotspot_password = "**YOUR HOTSPOT PASSWORD**";
#endif

//afterwards normal wifi will be tried
const char* ssid = "**YOUR SSID**";
const char* password = "**YOUR PASSWORD**";
//////////

void wifiConnected() {
  MQTTClient::activate();
  MQTTDebug::info("Connected to network!");
  MQTTDebug::info(concatString("Got IP: ", WiFi.localIP().toString().c_str()));
}

void setupWifi() {
  #ifdef USE_HOTSPOT
  //try hotspot connection first
  MQTTDebug::info("Connecting to hotspot ...");
  WiFi.begin(hotspot_ssid, hotspot_password);
  int delayed = 0;

  while (WiFi.status() != WL_CONNECTED && delayed < 6) {
    delay(1000);
    delayed++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    wifiConnected();
  } else {
  #endif
    MQTTDebug::info(concatString("Connecting to ", ssid));
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
    }

    wifiConnected();
  #ifdef USE_HOTSPOT
  }
  #endif
}
