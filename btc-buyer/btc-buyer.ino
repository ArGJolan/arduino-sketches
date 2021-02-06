#include "http.h"

void setup() {
  setupWifi();
}

void loop() {
  if (wifiReady()) {
    Serial.print(get("http://worldtimeapi.org/api/ip.txt"));
  } else {
    Serial.println("Error in WiFi connection");
  }
  delay(30000);
}
