#include <ESP8266WiFi.h>
char *ssid = "VIVO-9B28";
char *password = "57601B9B28";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  connectWiFi();
  pinMode(2, OUTPUT);
}

void initServer(){
    server.begin();
    Serial.println("Servidor inicializado");
}

bool connectWiFi(){
    Serial.println(ssid);
    Serial.print("Connecting to ");
    WiFi.begin(ssid, password);
    int count = 0;
    while (WiFi.status() != WL_CONNECTED && count < 20 ) {
      delay(500);      count++;
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi connected");
        initServer();
        return true;
    }
    Serial.println("WiFi disconnected");
    return false;
}


void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  String buf = "";

  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
  buf += "<html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  buf += "<title>ESP8266 Web Server</title>";
  buf += "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:80%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float: right;width: 64px;text-align: right;}</style>";
  buf += "</head>";
  buf += "<h3>ESP8266 Web Server</h3>";
  buf += "<p>LED <a href=\"?function=led2_on\"><button>ON</button></a> <a href=\"?function=led2_off\"><button>OFF</button></a></p>";
  buf += "</html>\n";

  client.print(buf);
  client.flush();

  if (req.indexOf("led2_on") != -1)
    digitalWrite(2, 0);
  else if (req.indexOf("led2_off") != -1)
    digitalWrite(2, 1);
  else {
    Serial.println("invalid request");
    client.stop();
  }
  Serial.println("Client disonnected");
}
