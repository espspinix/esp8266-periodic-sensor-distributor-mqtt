#include "MQTTClient.h"

#ifndef MQTTDEBUG_H
#define MQTTDEBUG_H 1

class MQTTDebug {
  protected:
  static const char* address;

  public:
  static int error(const char * sender, const char * message);
  static int info(const char * message);
};

#endif 
