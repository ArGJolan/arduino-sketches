// To boot the ESP8266 in normal mode, RESET & CH_PD (or EN) must be connected to VCC

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "secret.h"

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
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

void loop() {
  delay(5000);
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;    //Declare object of class HTTPClient

    http.begin("http://192.168.178.20:4242");      //Specify request destination
    http.addHeader("Content-Type", "text/plain");  //Specify content-type header

    int httpCode = http.POST("Message from ESP8266");   //Send the request
    String payload = http.getString();                  //Get the response payload

    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload

    http.end();  //Close connection
  } else {
    Serial.println("Error in WiFi connection");
  }
  delay(30000);  //Send a request every 30 seconds
}
