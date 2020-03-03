#include "SensorSampler.h"
#include "MQTTDebug.h"

SensorSampler::SensorSampler(int period) {
  SamplingPeriod = period;
  ErrorPeriod = 500;
  hasError = false;
}

void SensorSampler::update() {
  unsigned long currentMillis = millis();

  if ( hasError && currentMillis - previousMillis < ErrorPeriod) {
    return;
  }
  
  if (!hasError && currentMillis - previousMillis < SamplingPeriod) {
    return;
  }

  if (readVariables()) {
    if (hasError) {
      MQTTDebug::error(getName(), "reread successfull!");
    }
    hasError = false;
  } else {
    MQTTDebug::error(getName(), "could not read variables");
    hasError = true;
  }
  previousMillis = currentMillis;
}
