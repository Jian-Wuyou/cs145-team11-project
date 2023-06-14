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
    "-----END CERTIFICATE-----\n"

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

  reading_buffer[buf_counter][0] = hi;
  reading_buffer[buf_counter][1] = t;
  reading_buffer[buf_counter][2] = h;
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
  client->setCACert(root_ca_certificate);

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