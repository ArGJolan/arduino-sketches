#include <SoftwareSerial.h>
SoftwareSerial helloESP(2, 3);

void setup() {
  Serial.begin(9600);
  helloESP.begin(9600);
  delay(5000);
  Serial.println("Ready to receive message!");
}

void loop() {
  String message = "";

  while (helloESP.available()) {
    message = helloESP.readString();
  }

  if (message != "") {
    Serial.println(message);
  }
}
