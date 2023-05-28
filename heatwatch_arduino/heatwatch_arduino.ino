// Library used: DHT sensor library by Adafruit (Arduino will ask to install another library)

#include "DHT.h"

#define DHTPIN 2                                               // Change Pin Number as needed
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();
}

void loop() {
   delay(1000);                                                // Wait one second for the sensor (DHT 11)

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if(isnan(h) || isnan(t)){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hi = dht.computeHeatIndex(t, h, false);                // Heat Index in degree celsius

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(F(" Heat index: "));
  Serial.print(hi);
  Serial.print(F("°C\n"));
}
