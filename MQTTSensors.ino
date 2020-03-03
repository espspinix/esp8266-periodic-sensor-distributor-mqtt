#include "WiFiConnector.h"
#include "DHTSampler.h"
#include "RandomSampler.h"
#include "LEDBlinker.h"
#include "MQTTDistributor.h"
#include "WebServer.h"

LEDBlinker myBlinker(LED_BUILTIN);
DHTSampler myDHT(D3);
RandomSampler myRandom(10, 80);

struct MQTTInstruction instructions[] = {
  {"/sensors/living/temperature", &myDHT, DHTSampler::TEMPERATURE},
  {"/sensors/living/humidity", &myDHT, DHTSampler::HUMIDITY},
  {"/sensors/test/random", &myRandom, RandomSampler::VALUE},
};

MQTTDistributor myMQTTDistributor(instructions, sizeof(instructions));
WebServer myWebServer(&myDHT, &myBlinker);

void setup() {
  Serial.begin(115200);

  setupWifi();
}

void loop() {
  myBlinker.update();
  myDHT.update();
  myWebServer.update();
  myMQTTDistributor.update();
  myRandom.update();
}
