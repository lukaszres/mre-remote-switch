#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "SSID";
const char* password = "password";
const char* hostname = "esp-serwer";
const char* requestPath = "/";
const int pinOut = LED_BUILTIN;

ESP8266WebServer server(80);

unsigned long lastRequestTime = 0;
const unsigned long ledTimeout = 2000; // 2 sekundy

void handleRequest() {
  Serial.println("Otrzymano żądanie!");
  digitalWrite(pinOut, LOW); // LED ON
  lastRequestTime = millis();
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  pinMode(pinOut, OUTPUT);
  digitalWrite(pinOut, HIGH); // LED OFF

  WiFi.begin(ssid, password);
  WiFi.hostname(hostname);

  Serial.print("Łączenie z WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println("\nPołączono!");
  Serial.print("Adres IP: ");
  Serial.println(WiFi.localIP());

  server.on(requestPath, handleRequest);
  server.begin();
  Serial.println("Serwer HTTP uruchomiony");
}

void loop() {
  server.handleClient();

  // Wyłącz LED po 2 sekundach od ostatniego żądania
  if (millis() - lastRequestTime > ledTimeout) {
    digitalWrite(pinOut, HIGH); // LED OFF
  }
}
