# esp8266-periodic-sensor-distributor-mqtt
Distributes multiple sensor values over MQTT in a defined interval on a ESP8266

# SensorSampler
Every sensor type needs a SensorSampler. There are already two sensor types implemented: DHT temperature/humidity sensor and a rather for test purposes written random sensor, which just outputs random numbers in a defined range.

# MQTTDistributor
The MQTTDistributor receives an array with instructions, these contain a topic, an instance of a SensorSampler subclass (e.g. DHTSampler) and the variable to be published. It will publish the variable in a predefined interval.
The MQTTDistributor supports multiple sensors with multiple variables.

# WebServer
Currently only supporting on DHT sensor for the Webserver.

# Examples
See the code, e.g. MQTTSensors.ino and DHTSampler.h for a SensorSampler implementation.
You can also just try to compile the code, please do not forget to copy WiFiConnector.example.h to WiFiConnector.h and fill out your wifi credentials.

Optionally a hotspot connecting is supported. On startup the esp will try to connect to a specified hotspot ssid for 6 seconds, before finally trying to connect to the main ssid. Useful for demonstrations in the public.
