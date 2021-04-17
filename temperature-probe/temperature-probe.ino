#include "http.h"
#include "temperature.h"
#include "temperature-probe.h"
#include <ArduinoOTA.h>

void postTemperature() {
  float temperature;
  temperature = get_temperature(A0);
  String result = post(
    String(API_ENDPOINT) + String("/temperature"),
    String("{ \"value\": ")
      + String(temperature)
      + String(", \"id\": \"")
      + String(ESP.getChipId())
      + String("\" }")
  );
}

void setup() {
  setupWifi();
  Serial.begin(9600);
  ArduinoOTA.begin();
  postTemperature();
  // ESP.deepSleep(1e6);
}

void loop() {
  ArduinoOTA.handle();
}
