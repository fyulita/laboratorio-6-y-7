#include <SoftwareSerial.h>
#include <Wire.h>
#include <Arduino.h>
#include "MHZ19.h"

#define RX_PIN 10
#define TX_PIN 11
#define BAUDRATE 966 //frecuencia a la que va a abrir el puerto serial

MHZ19 myMHZ19;
SoftwareSerial mySerial(RX_PIN, TX_PIN);

void setup(){
Serial.begin(9600);
  mySerial.begin(BAUDRATE);
  myMHZ19.begin(mySerial);

  myMHZ19.autoCalibration();
}

void loop() {
  static int CO2 =0;
  CO2 = myMHZ19.getCO2();
  Serial.print("CO2 (ppm):");
  Serial.println(CO2);
  delay(1000);
  
}
