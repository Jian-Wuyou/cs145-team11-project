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