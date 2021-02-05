// #include <ArduinoJson.h>
#include <SoftwareSerial.h>
SoftwareSerial fromESP(2, 3);

void debug(String content) {
  Serial.print("DEBUG_REQUEST_RESULT " + content);
}

void setup() {
  Serial.begin(9600);
  fromESP.begin(9600);

  delay(5000);
}

String post(String url, String payload) {
  debug("Post");

  Serial.print("POST\n" + url + "\n" + payload);
  String result = "";

  while (result == "") {
    while (fromESP.available()) {
      result = fromESP.readString();
    }
  }

  return result;
}

String get(String url) {
  debug("Get");

  Serial.print("GET\n" + url + "\n");
  String result = "";

  while (result == "") {
    while (fromESP.available()) {
      result = fromESP.readString();
    }
  }

  return result;
}

void loop() {
  Serial.print("http://192.168.178.36:4365/humidity");

  String result = "";

  while (result == "") {
    while (fromESP.available()) {
      result = fromESP.readString();
    }
  }
  Serial.print("http://192.168.178.36:4365/DONE" + result);
  delay(60000);
  // long randNumber = random(100);

  // String result = post("http://192.168.178.36:4365/humidity", String("{ \"value\": ") + randNumber + String(" }"));
  
  // debug("RESULT: " + result);
}
