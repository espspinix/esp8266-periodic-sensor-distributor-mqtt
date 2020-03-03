#include "DHT.h"
#include "SensorSampler.h"

// Uncomment one of the lines below for whatever DHT sensor type you're using!
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

class DHTSampler : public SensorSampler {
  DHT dht;
  uint8_t DHTPin;
  float temperature;
  float humidity;

  public:
  enum Variables { TEMPERATURE, HUMIDITY };
  const char * name = "DHT";

  DHTSampler(uint8_t pin = D3) : SensorSampler() {
    DHTPin = pin;
    pinMode(DHTPin, INPUT);
    dht.setup(DHTPin, DHT::DHT22);
    SamplingPeriod = dht.getMinimumSamplingPeriod();

    while(isnan(dht.getTemperature()) || isnan(dht.getHumidity())) {
      delay(SamplingPeriod);
    }
  }

  const char * getName() {
    return name;
  }

  String get(int variable) {
    switch(variable) {
      case TEMPERATURE:
        return String(temperature);
      case HUMIDITY:
        return String(humidity);
    }

    return "";
  }

  int readVariables() {
    float currentTemperature = dht.getTemperature();
    float currentHumidity = dht.getHumidity();

    if (isnan(currentTemperature) || isnan(currentHumidity)) {
      return false;
    }

    temperature = currentTemperature;
    humidity = currentHumidity;
    return true;
  }
};
