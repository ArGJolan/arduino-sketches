// #include <ArduinoJson.h>
#include <SoftwareSerial.h>
SoftwareSerial fromESP(2, 3);

void setup() {
  Serial.begin(9600);
  fromESP.begin(9600);

  delay(5000);
}

String post(String url, String payload) {
  int count = 0;

  Serial.print("POST\n" + url + "\n" + payload);
  String result = "";

  while (result == "" && count < 500) {
    while (fromESP.available()) {
      result = fromESP.readString();
      delay(10);
      count++;
    }
  }

  return result;
}

String get(String url) {
  int count = 0;

  Serial.print("GET\n" + url + "\n");
  String result = "";

  while (result == "" && count < 500) {
    while (fromESP.available()) {
      result = fromESP.readString();
      delay(10);
      count++;
    }
  }

  return result;
}

void loop() {
  long randNumber = random(100);

  String result = post("http://192.168.178.36:4365/humidity", String("{ \"value\": ") + randNumber + String(" }"));

  delay(60000);
}
