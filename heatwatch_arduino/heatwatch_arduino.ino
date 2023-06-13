#include <HTTPClient.h>
#include <time.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RX_PIN 16
#define TX_PIN 17

// Configuring the clock
const char* ntpServer[] = {"1.ph.pool.ntp.org",
                           "1.asia.pool.ntp.org",
                           "2.asia.pool.ntp.org"};
const long  gmtOffset_sec = 28800;
const int   daylightOffset_sec = 0;

// Configuring webserver connection
String server = "https://heatwatch.up.railway.app";
const int MAX_BUF_SIZE = 100;
const int CLR_BUF_SIZE = 2;              // Clear buffer after it exceeds this threshold
int buf_counter = 0;                      // Send data when buf_counter == MAX_BUF_SIZE
float (*reading_buffer)[3];    // Heat Index, Temperature, Humidity
int64_t *timestamp_buffer;   // Time in ms

// *.up.railway.app certificate
// Expires on July 15, 2023
const char* root_ca_certificate = "-----BEGIN CERTIFICATE-----\n" \
  "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\n" \
  "-----END CERTIFICATE-----\n";

void get_readings();
void send_readings();
void set_clock();
int64_t xx_time_get_time();

WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  reading_buffer = (float (*)[3]) malloc(MAX_BUF_SIZE * sizeof(*reading_buffer));
  timestamp_buffer = (int64_t*) malloc(MAX_BUF_SIZE * sizeof(*timestamp_buffer));

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Lenovo T450", "jhgfuiyu");

  // Connect to WiFi network
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Configure time from NTP servers
  set_clock();
}

void loop() {
  delay(1000);
  get_readings();
}

void get_readings() {
  if(buf_counter >= MAX_BUF_SIZE) {
    Serial.println("Buffer full, cannot upload new data to server.");
    return;
  }

  timestamp_buffer[buf_counter] = xx_time_get_time();

  String data = Serial2.readString();
  data.trim();

  float h, t, hi;
  sscanf(data.c_str(), "%f %f %f", &h, &t, &hi);

  Serial.println(data);
  // Serial.println(d);

  // TODO: replace with sensor readings
  reading_buffer[buf_counter][0] = h;
  reading_buffer[buf_counter][1] = t;
  reading_buffer[buf_counter][2] = hi;
  buf_counter++;

  if(buf_counter >= CLR_BUF_SIZE) {
    send_readings();
  }
}

void send_readings() {
  WiFiClientSecure *client = new WiFiClientSecure;
  if(!client) {
    Serial.println("Unable to create client");
    return;
  }
  client->setInsecure();
  // client->setCACert(root_ca_certificate);

  

  String json = "{ \"readings\": [";
  char *temp = (char*)malloc(4096);
  for(int i = 0, n = 0; i < buf_counter; i++) {
    n = sprintf(temp + n, "[%lld, %.3f, %.3f, %.3f]%c",
      timestamp_buffer[i], reading_buffer[i][0], reading_buffer[i][1], reading_buffer[i][2], i + 1 == buf_counter ? ']' : ',');
  }
  json += temp;
  json += "}";
  Serial.println(json);
  free(temp);

  {
    HTTPClient https;
    Serial.print("[HTTPS] begin...\n");
    if(https.begin(*client, server + "/update_db")) {
      Serial.print("[HTTPS] POST...\n");
      https.addHeader("Content-Type", "application/json");
      int http_code = https.POST(json);

      if(http_code > 0) {
        Serial.printf("[HTTPS] POST... code: %d\n", http_code);
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(http_code).c_str());
      }
      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }

  delete client;

  buf_counter = 0;
}

// Gets time in milliseconds
int64_t xx_time_get_time() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + (tv.tv_usec / 1000LL));
}

void set_clock() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer[0], ntpServer[1], ntpServer[2]);

  Serial.print(F("Waiting for NTP time sync: "));
  time_t nowSecs = time(nullptr);
  while (nowSecs < 8 * 3600 * 2) {
    delay(500);
    Serial.print(F("."));
    yield();
    nowSecs = time(nullptr);
  }

  Serial.println();
  struct tm timeinfo;
  gmtime_r(&nowSecs, &timeinfo);
  Serial.print(F("Current time: "));
  Serial.print(asctime(&timeinfo));
}