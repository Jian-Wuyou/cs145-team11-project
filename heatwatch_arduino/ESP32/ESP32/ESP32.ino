#define RX_PIN 16
#define TX_PIN 17

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println(Serial2.readString());
  delay(200);

  

}
