#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int boardState = 0;
int buttonState = 0;
int prevButtonState;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();

  pinMode(3, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  prevButtonState = buttonState;
  buttonState = digitalRead(3);
  
  if (buttonState == 0 && prevButtonState == 1){
    boardState = (boardState + 1) % 2;
  }

  if (boardState == 1){
    readSensor();
  }
}

void readSensor(){
  delay(1000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();    

  if(isnan(h) || isnan(t)){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hi = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(F(" Heat index: "));
  Serial.print(hi);
  Serial.print(F("°C\n"));
}
