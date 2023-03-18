#include <WiFi.h>

const char* ssid = "ESP32-AP"; // SSID of the hotspot
const char* password = "password123"; // Password of the hotspot

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Set ESP32 to Access Point mode
  WiFi.mode(WIFI_AP);
  
  // Configure the access point
  WiFi.softAP(ssid, password);

  // Get the IP address of the access point
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

void loop() {
  // Do nothing
}
