#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "secret.h"

SoftwareSerial fromArduino(2, 0);

void debug(String message) {
  Serial.print("DEBUG_FROM_ESP: " + message + "\n");
}

void setup() {
  Serial.begin(9600);
  fromArduino.begin(9600);

  debug("STARTING");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    debug("CONNECTING TO WIFI");
    delay(100);
  }
  debug("CONNECTED");

  delay(5000);
}

String post(char *url, char *payload) {
  debug("Sending post to" + String(url));
  HTTPClient http;

  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(payload);

  return httpCode + String(":") + http.getString();
}

String get(char *url) {
  debug("Sending get to" + String(url));
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
      // Cancer string convertion
      const char *constRequest = request.c_str();
      char *properRequest = (char *)malloc((strlen(constRequest) + 1) * sizeof(char));
      properRequest = (char*)memset(properRequest, 0, (strlen(constRequest) + 1) * sizeof(char));
      strcpy(properRequest, constRequest);

      String result = get(properRequest);

      Serial.print(result);
    } else {
      debug("wifierror");
    }
  //} else {
  //  String message = "Nothing sent";
  //  debug(message);
  }
}
