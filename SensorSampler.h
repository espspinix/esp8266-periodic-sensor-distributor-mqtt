#include <Arduino.h>

#ifndef SENSORSAMPLER_H
#define SENSORSAMPLER_H 1

class SensorSampler {
  unsigned long previousMillis = 0;
  
  public: 
  SensorSampler(int period = 2000);
  void update();
  
  virtual String get(int variable) {};
  virtual int readVariables() {};
  virtual const char * getName() = 0;
  const char * name;

  protected:
  int SamplingPeriod;
  int ErrorPeriod;
  int hasError;
};

#endif 
