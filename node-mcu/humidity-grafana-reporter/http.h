#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "secret.h"

void setupWifi();
String post(char *url, char *payload);
String get(char *url);
String post(String url, String payload);
String get(String url);
bool wifiReady();
