#include  <HardwareSerial.h>
#include  "http.h"

void setup() {
  Serial.begin(9600);

  setupWifi();
  Serial.print("Starting up...");
}

void loop() {
  long randNumber = random(100);

  String result = post("http://192.168.178.36:4365/humidity", String("{ \"value\": ") + String(randNumber) + String(" }"));

  Serial.println(result);

  delay(60000);
}
