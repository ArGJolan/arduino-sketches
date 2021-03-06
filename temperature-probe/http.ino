#include "http.h"

void setupWifi() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    if (WIFI_DEBUG) {
      Serial.println("Waiting for connection");
    }
  }
  if (WIFI_DEBUG) {
    Serial.println("Connected to " + String(WIFI_SSID));
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

String post(String url, String payload) {
  HTTPClient http;

  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(payload);

  return httpCode + String(":") + http.getString();
}

String get(String url) {
  HTTPClient http;

  http.begin(url);
  int httpCode = http.GET();

  return httpCode + String(":") + http.getString();
}

bool wifiReady() {
  return WiFi.status() == WL_CONNECTED;
}
