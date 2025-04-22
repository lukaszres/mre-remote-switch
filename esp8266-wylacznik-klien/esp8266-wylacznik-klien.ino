#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "SSID";
const char* password = "password";
const char* hostname = "esp-wylacznik";
const char* serverUrl = "http://192.168.0.109";

unsigned long lastRequestTime = 0;
const unsigned long interval = 1000; // 1 sekunda

WiFiClient client;  // dodajemy klienta TCP

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  WiFi.hostname(hostname);

  Serial.print("Łączenie z WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println("\nPołączono z WiFi!");
  Serial.print("Adres IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  unsigned long currentTime = millis();

  if (WiFi.status() == WL_CONNECTED && currentTime - lastRequestTime >= interval) {
    lastRequestTime = currentTime;

    HTTPClient http;
    http.begin(client, serverUrl);  // <--- poprawione wywołanie

    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.printf("Odpowiedź serwera [%d]: %s\n", httpCode, http.getString().c_str());
    } else {
      Serial.printf("Błąd żądania: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  // Możesz tu umieścić inne rzeczy
}
