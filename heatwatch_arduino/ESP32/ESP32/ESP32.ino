#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#define RX_PIN 16
#define TX_PIN 17

const char* ssid = "";       // CHANGE 
const char* password = "";  // CHANGE

WebServer server(80);

String data;

void handleRoot(){
  String html = "<html><body>";
  html += "<h1> Sensor Data</h1>";
  html += "<p>" + data + "%</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // put your main code here, to run repeatedly:
  data = Serial2.readString();
  Serial.println(data);
  
  server.handleClient();
  
  delay(200);

  

}
