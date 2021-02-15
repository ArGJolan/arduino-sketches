#include  "http.h"
#include  "humidity-grafana-reporter.h"

void setup() {
  setupWifi();
  
  int humidity = analogRead(A0);
  int percentHumidity = map(humidity, SENSOR_WET, SENSOR_DRY, 100, 0);

  String result = post(String(API_ENDPOINT) + String("/humidity"), String("{ \"value\": ") + String(percentHumidity) + String(" }"));

  ESP.deepSleep(3600e6);
}

void loop() {

}
