#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "SSID";
const char* password = "password";
const char* hostname = "esp-serwer";
const char* requestPath = "/";

ESP8266WebServer server(80);

unsigned long lastRequestTime = 0;
const unsigned long ledTimeout = 2000; // 2 sekundy

void handleRequest() {
  Serial.println("Otrzymano żądanie!");
  digitalWrite(LED_BUILTIN, LOW); // LED ON (na ESP8266 LOW = zapalony)
  lastRequestTime = millis();
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // LED OFF (domyślnie zgaszona)

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
    digitalWrite(LED_BUILTIN, HIGH); // LED OFF
  }
}
