#include <Arduino.h>
#include <SoftwareSerial.h>

#define rxPin 8
#define txPin 9

SoftwareSerial ss (rxPin, txPin, 1);

void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  ss.begin(2400);

  Serial.begin(115200);
}

void loop() {
  ss.write("D\r");
  char buffer[256];
  int pos = 0;
  bool lineStart = false;
  while(ss.available()) {
    char r = ss.read();
    if ( r == '#' ) {
      lineStart = true;      
    }
    if ( r == '\r' ) {
      Serial.write(buffer, pos);
      lineStart = false;
      pos = 0;
      break;      
    }
    if ( lineStart ) {
      buffer[pos++] = r;
    }
  }
  Serial.print("\r\n");
  delay(3000);
}