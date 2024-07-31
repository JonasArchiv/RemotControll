#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "WLAN_SSID"; // WLAN-SSID
const char* password = "WLAN_Passwort"; // WLAN-Passwort
const char* apiKey = "YOUR_API_KEY"; // API-Schlüssel

const int buttonPins[] = {5, 4, 0, 2, 14, 12, 13}; // GPIO-Pins für D1 bis D7
const char* urls[] = {
  "http://example.com/api/d1",
  "http://example.com/api/d2",
  "http://example.com/api/d3",
  "http://example.com/api/d4",
  "http://example.com/api/d5",
  "http://example.com/api/d6",
  "http://example.com/api/d7"
};

// Beispiel für benutzerdefinierte JSON-Daten je nach URL
const char* jsonData[] = {
  "{\"key1\":\"value1\"}", // JSON-Daten für URL 1
  "{\"key2\":\"value2\"}", // JSON-Daten für URL 2
  "{\"key3\":\"value3\"}", // JSON-Daten für URL 3
  "{\"key4\":\"value4\"}", // JSON-Daten für URL 4
  "{\"key5\":\"value5\"}", // JSON-Daten für URL 5
  "{\"key6\":\"value6\"}", // JSON-Daten für URL 6
  "{\"key7\":\"value7\"}"  // JSON-Daten für URL 7
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
      sendHttpRequest(urls[i], jsonData[i]);
      delay(500); // Schutz vor Spam
    }
  }
}

void sendHttpRequest(const char* url, const char* json) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url);
    http.addHeader("Authorization", apiKey); // API-Schlüssel als Header hinzufügen
    http.addHeader("Content-Type", "application/json"); // JSON-Header hinzufügen
    
    int httpCode = http.POST(json); // JSON-Daten senden
    if (httpCode > 0) {
      Serial.printf("HTTP Request sent, response code: %d\n", httpCode);
    } else {
      Serial.printf("HTTP Request failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}