#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "WLAN_SSID";
const char* password = "WLAN_Password";

const int buttonPins[] = {2, 3, 4, 5, 6, 7, 8}; // Pins
const char* urls[] = {
  "http://example.com/api/p1",
  "http://example.com/api/p2",
  "http://example.com/api/p3",
  "http://example.com/api/p4",
  "http://example.com/api/p5",
  "http://example.com/api/p6",
  "http://example.com/api/p7"
};

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  for (int i = 0; i < 7; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < 7; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      sendHttpRequest(urls[i]);
      delay(500); // Prevent SPAM
    }
  }
}

void sendHttpRequest(const char* url) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.printf("HTTP Request sent, response code: %d\n", httpCode);
    } else {
      Serial.printf("HTTP Request failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}
