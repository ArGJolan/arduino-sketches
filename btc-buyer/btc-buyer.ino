#include "http.h"
#include "date.h"

void setup() {
  setupWifi();
}

void loop() {
  if (wifiReady()) {
    String currentTime = currentIsoString();
    String currentDay = getMonthDay(currentTime);
    int day = currentDay.toInt();

    Serial.print(day);
  } else {
    Serial.println("Error in WiFi connection");
  }
  delay(30000);
}
