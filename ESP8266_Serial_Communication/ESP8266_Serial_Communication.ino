#include <SoftwareSerial.h>
#define RX 7
#define TX 8
SoftwareSerial esp8266(RX, TX);

//the setup routine runs once you press reset;
void setup() {
  //initiate the hardeware serial port.
  Serial.begin(115200);
  esp8266.begin(115200);
  delay(2000);

}

//the loop routine runs over and over again forever;
void loop() {
  //esp8266.print('!');
  //we check if we have recived anything on the serial port
  if (esp8266.available() > 0) {
    char b = esp8266.read();
    Serial.print(b);
  }
  if (Serial.available() > 0) {
    char b = Serial.read();
    esp8266.print(b);
  }
}

