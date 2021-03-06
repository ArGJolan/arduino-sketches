#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "secret.h"

SoftwareSerial fromArduino(2, 0);

void debug(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    get("http://192.168.178.36:4365/debug");
    get("http://192.168.178.36:4365/debug" + message);
  //} else {
  //  Serial.print(message);
  }
}

void setup() {
  Serial.begin(9600);
  fromArduino.begin(9600);

  debug("Starting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    debug("CONNECTING TO WIFI");
    delay(100);
  }
  debug("CONNECTED");

  delay(5000);
}

String post(char *url, char *payload) {
  HTTPClient http;

  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(payload);

  return httpCode + String(":") + http.getString();
}

String get(char *url) {
  HTTPClient http;

  http.begin(url);
  int httpCode = http.GET();

  return httpCode + String(":") + http.getString();
}

String get(String url) {
  HTTPClient http;

  http.begin(url);
  int httpCode = http.GET();

  return httpCode + String(":") + http.getString();
}

void loop() {
  String request = "";

  while (fromArduino.available()) {
    request = fromArduino.readString();
  }

  if (request != "") {
    if (WiFi.status() == WL_CONNECTED) {
      debug("GOT MESSAGE" + request);
      /*
      ** Format of requests:
      **
      ** "GET
      **  http://totoland.site"
      **
      ** "POST
      **  http://totoland.site
      **  {\"toto\": 42}"
      */

      debug("Received request" + request);
      String result;

      // Cancer string convertion
      const char *constRequest = request.c_str();
      char *properRequest = (char *)malloc((strlen(constRequest) + 1) * sizeof(char));
      properRequest = (char*)memset(properRequest, 0, (strlen(constRequest) + 1) * sizeof(char));
      strcpy(properRequest, constRequest);

      String debugUrl = String("http://192.168.178.36:4365/debug") + String(properRequest);
      get("http://192.168.178.36:4365/debug");

      // Fetch method & url from request
      char *method = strtok(properRequest, "\n");
      char *url = strtok(NULL, "\n");

      debug("METHOD:" + String(method));
      debug("URL:" + String(url));

      if (strcmp(method, "post") == 0 || strcmp(method, "POST") == 0) {
        char *payload = strtok(NULL, "\n");
        debug("PAYLOAD:" + String(payload));
        if (method == NULL || url == NULL || payload == NULL) {
          result = "Need to provide method, url and payload on 3 lines";
        } else {
          result = post(url, payload);
        }
      } else if (strcmp(method, "get") == 0 || strcmp(method, "GET") == 0) {
        if (method == NULL || url == NULL) {
          result = "Need to provide method and url on 2 lines";
        } else {
          result = get(url);
        }
      } else {
        result = "Method not handled " + String(method);
      }

      Serial.print(result);
      delay(100);
      ESP.deepSleep(30e6);
    } else {
      debug("wifierror");
    }
  //} else {
  //  String message = "Nothing sent";
  //  debug(message);
  }
}
