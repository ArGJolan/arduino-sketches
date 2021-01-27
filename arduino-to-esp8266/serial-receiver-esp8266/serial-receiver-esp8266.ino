#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "secret.h"

SoftwareSerial helloArduino(2, 0);

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
  helloArduino.begin(9600);
  delay(5000);
  Serial.println("Ready to receive message!");
}

void loop() {
  String message = "";

  while (helloArduino.available()) {
    message = helloArduino.readString();
  }

  if (message != "") {
    Serial.println(message);

    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
      HTTPClient http;    //Declare object of class HTTPClient
   
      http.begin("http://192.168.178.20:4242/" + message);      //Specify request destination
      http.addHeader("Content-Type", "text/plain");  //Specify content-type header
   
      int httpCode = http.POST("Message from ESP8266 \"" + message + "\"");   //Send the request
      String payload = http.getString();                  //Get the response payload
   
      Serial.println(httpCode);   //Print HTTP return code
      Serial.println(payload);    //Print request response payload
   
      http.end();  //Close connection
    } else {
      Serial.println("Error in WiFi connection");
    }
  }
}
