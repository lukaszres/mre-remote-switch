1. **mre-remote-switch\esp8266-wylacznik-klien\esp8266-wylacznik-klien.ino**  
   const char* ssid = "SSID";  
   const char* password = "password";  
   const char* serverUrl = "http://192.168.0.109";  

   Opcjonalnie możesz też poprawić:  
   const char* hostname = "esp-wylacznik";  
   const unsigned long interval = 1000; // 1 sekunda  
  
2. **mre-remote-switch\esp8266-wylacznik-serwer/C:\Users\lukas\Documents\Arduino\Projects\mre-remote-switch\esp8266-wylacznik-serwer.ino**
   const char* ssid = "SSID";  
   const char* password = "password";  
  
   Opcjonalnie możesz też poprawić:  
      const char* hostname = "esp-serwer";  
      const char* requestPath = "/"; // jeśli to zmienisz, to musisz też poprawić serverUrl w esp8266-wylacznik-klien.ino  
      const unsigned long ledTimeout = 2000; // 2 sekundy  
