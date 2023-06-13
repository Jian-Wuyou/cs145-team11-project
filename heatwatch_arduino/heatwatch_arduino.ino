#include <time.h>
#include <WiFi.h>
#include <WiFiClient.h>

const char* ssid = "";       // CHANGE 
const char* password = "";  // CHANGE

// Configuring the clock
const char* ntpServer[] = {"1.ph.pool.ntp.org",
                           "1.asia.pool.ntp.org",
                           "2.asia.pool.ntp.org"};
const long  gmtOffset_sec = 28800;
const int   daylightOffset_sec = 0;

// Configuring webserver connection
const char* webserver = "https://heatwatch.up.railway.app";
const int MAX_BUF_SIZE = 10;
int buf_counter = 0;                   // Send data when buf_counter == MAX_BUF_SIZE
float reading_buffer[MAX_BUF_SIZE][3]; // Heat Index, Temperature, Humidity
int64_t timestamp_buffer[MAX_BUF_SIZE];  // Time in ms

// *.up.railway.app certificate
// Expires on July 15, 2023
const char* root_ca = "-----BEGIN CERTIFICATE-----\n" \
  "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\n" \
  "-----END CERTIFICATE-----\n";

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Configure time from NTP servers
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer[0], ntpServer[1], ntpServer[2]);
  Serial.println(xx_time_get_time());

}

void loop(){
  delay(500);
  get_readings();
}

void get_readings() {
  timestamp_buffer[buf_counter] = xx_time_get_time();

  // TODO: replace with sensor readings
  reading_buffer[buf_counter][0] = 0;
  reading_buffer[buf_counter][1] = 0;
  reading_buffer[buf_counter][2] = 0;
  buf_counter++;

  if(buf_counter == MAX_BUF_SIZE) {
    send_readings();
  }
}

void send_readings() {
  String json = "{ \"readings\": [";
  char temp[500];
  for(int i = 0; i < buf_counter; i++) {
    sprintf(temp, "[%lld, %.3f, %.3f, %.3f]%c",
            timestamp_buffer[i], reading_buffer[i][0], reading_buffer[i][1], reading_buffer[i][2], i + 1 == buf_counter ? ']' : ',');
    json += temp;
  }
  json += "}";
  buf_counter = 0;
  Serial.println(json);

  // TODO: send json to server
}

// Gets time in milliseconds
int64_t xx_time_get_time() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + (tv.tv_usec / 1000LL));
}