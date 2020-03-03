#include <ESP8266WebServer.h>
#include "MQTTDebug.h"

class WebServer {
  ESP8266WebServer server;

  LEDBlinker * myBlinker;
  DHTSampler * myDHT;

  public: WebServer(DHTSampler *dhtModule, LEDBlinker *blinkerModule) : server(80), myBlinker(blinkerModule), myDHT(dhtModule) {
    initServer();
  }

  WebServer(DHTSampler *dhtModule) : server(80), myDHT(dhtModule) {
    initServer();
  }

  void initServer() {
    server.on("/", std::bind(&WebServer::serveDHTOutput, this));
    server.onNotFound(std::bind(&WebServer::pageNotFound, this));
    server.begin();

    MQTTDebug::info("HTTP server started");
  }

  void pageNotFound(){
    const char * output = "Page not found, please try <a href='/'>this link</a>";
    server.send(404, "text/plain", output);
  }

  void serveDHTOutput() {
    String temperature = myDHT->get(DHTSampler::TEMPERATURE);
    String humidity = myDHT->get(DHTSampler::HUMIDITY);

    #ifdef DEBUG
    myBlinker->blink(2, 5);
    Serial.println(temperature);
    Serial.println("Sending Server Response..");
    #endif

    server.send(200, "text/html", formatDHTOutput(temperature, humidity));
  }

  String headerHTML(String title) {
    String output = "<!DOCTYPE html> <html>\n"
      "<head>"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n"
        "<meta http-equiv=\"refresh\" content=\"2\">"
        "<title>" + title + "</title>\n"
        "<style>\n"
          "html { font-family: Helvetica; display: inline-block; margin: 0px auto;"
            " text-align: center; }\n"
          "body{ margin-top: 20px; }\n"
          "h1 { color: #19b8c8; margin: 50px auto 30px; }\n"
          "p { font-size: 24px; color: #2a7799; margin-bottom: 10px; }\n"
        "</style>\n"
      "</head>\n"
      "<body>\n";
    return output;
  }

  String footerHTML() {
    String output = ""
      "</body>\n"
      "</html>\n";
    return output;
  }

  String sensorHTML(
    String sensorName,
    String temperature,
    String humidity
  ) {
    String output = ""
      "<div class=\"sensor\">\n"
        "<h1>" + sensorName + "</h1>\n"
        "<p>temperature: " + temperature + "C</p>\n"
        "<p>humidity: " + humidity + "%</p>\n"
      "</div>\n";
      return output;
  }

  String formatDHTOutput(String temperature, String humidity){
    String output = ""
      "" + headerHTML("DHT Sensor Example") + ""
      "" + sensorHTML("DHT Sensor", temperature, humidity) + ""
      "" + footerHTML();
    return output;
  }

  void update() {
    server.handleClient();
  }
};
