#include <ESP8266WiFi.h>
char *ssid = "VIVO-9B28";
char *password = "57601B9B28";

void setup() {
  Serial.begin(115200);
  delay(10);
  connectWiFi();
}

bool connectWiFi(){
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    int count = 0;
    while (WiFi.status() != WL_CONNECTED && count < 20 ) {
      delay(500);      count++;
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi connected");
        return true;
    }
    Serial.println("WiFi disconnected");
    return false;
}

void loop() {
  delay(2000);
  Serial.println(WiFi.localIP());
}
