<<<<<<< HEAD
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
=======
const int pinRelay1 = 7;
const int pinRelay2 = 8;


void setup() {
    //Para el relay:
    pinMode(pinRelay, OUTPUT); //conexión a S del relay
}
 

void loop() {
    digitalWrite(pinRelay1, HIGH); //turn relay ON
    digitalWrite(pinRelay2, HIGH);
    Serial.println("Prendido");
    delay(5000);
    digitalWrite(pinRelay1, LOW);
    digitalWrite(pinRelay2, LOW)//turn relay OFF
    Serial.println("Apagado");
    }
    delay(5000); 
}
>>>>>>> d8c288ad8b1b429656b57d21cb34699d3f6f3e5e
