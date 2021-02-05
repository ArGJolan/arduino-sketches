#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "secret.h"

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
  Serial.println("Ready to receive message!");
}

void loop() {
  String message = "";

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;    //Declare object of class HTTPClient
  
    http.begin("http://192.168.178.36:4365/humidity");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
  
    int httpCode = http.POST("{ \"value\": 42 }");   //Send the request
    String payload = http.getString();                  //Get the response payload
  
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
  
    http.end();  //Close connection
  } else {
    Serial.println("Error in WiFi connection");
  }
  delay(5000);
}
