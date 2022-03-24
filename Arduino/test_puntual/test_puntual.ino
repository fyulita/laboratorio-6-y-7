#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <MHZ19.h>
#include <SoftwareSerial.h>


#define baudrate 9600
#define pinDatosDQ 2
#define pinRelayTemp 3
#define pinRelayValvulaCO2_1 4
#define pinRelayValvulaCO2_2 6
#define pinRelayValvulaCO2_3 8
#define pinRelayValvulaCO2_4 10
#define pinRelayValvulaCompost_1 5
#define pinRelayValvulaCompost_2 7
#define pinRelayValvulaCompost_3 9
#define pinRelayValvulaCompost_4 11
#define pinRx 12
#define pinTx 13


// Constructors
OneWire myOneWire(pinDatosDQ);
DallasTemperature sensorDS18B20(&myOneWire);
MHZ19 myMHZ19;
SoftwareSerial mySerial(pinRx, pinTx);


// Time intervals

#define compostTime 10000// 14400000 // 4h
#define co2Time 20000// 1800000 // 30 mins.

const int loopTime = 5000;
unsigned long currentTime = 0;
unsigned long previousTime = 0;


// Which CO2 sensor is being used. 0 means the sensor isn't being used.
int useSensor = 0;


// Cutoff temperature for the compost
const unsigned int cutoffTemp = 60;


void setup() {
    // Serials
    Serial.begin(baudrate);
    mySerial.begin(baudrate);

    sensorDS18B20.begin(); 
    myMHZ19.begin(mySerial);

    // Relay pins
    pinMode(pinRelayTemp, OUTPUT);
    pinMode(pinRelayValvulaCO2_1, OUTPUT);
    pinMode(pinRelayValvulaCO2_2, OUTPUT);
    pinMode(pinRelayValvulaCO2_3, OUTPUT);
    pinMode(pinRelayValvulaCO2_4, OUTPUT);
    pinMode(pinRelayValvulaCompost_1, OUTPUT);
    pinMode(pinRelayValvulaCompost_2, OUTPUT);
    pinMode(pinRelayValvulaCompost_3, OUTPUT);
    pinMode(pinRelayValvulaCompost_4, OUTPUT);

    // Calibrate CO2 sensor
    myMHZ19.autoCalibration();

    // Initialize valves
    digitalWrite(pinRelayValvulaCO2_1, LOW);
    digitalWrite(pinRelayValvulaCO2_2, LOW);
    digitalWrite(pinRelayValvulaCO2_3, LOW);
    digitalWrite(pinRelayValvulaCO2_4, HIGH); //LEO EL 4 INDEFINIDO TIEMPO
    digitalWrite(pinRelayValvulaCompost_1, HIGH);
    digitalWrite(pinRelayValvulaCompost_2, HIGH);
    digitalWrite(pinRelayValvulaCompost_3, HIGH);
    digitalWrite(pinRelayValvulaCompost_4, LOW); //LEO EL 4 INDEFINIDO TIEMPO
}

 
void loop() {
    // CO2 sensor
    Serial.print(myMHZ19.getCO2());
    Serial.print(",");

    // millis() can run without an overflow for up to 5 months
    currentTime = millis();

    

    // Temperature sensors
    sensorDS18B20.requestTemperatures();
    Serial.print(sensorDS18B20.getTempCByIndex(0));
    Serial.print(",");
    Serial.print(sensorDS18B20.getTempCByIndex(1));
    Serial.print(",");
    Serial.print(sensorDS18B20.getTempCByIndex(2));
    Serial.print(",");
    Serial.print(sensorDS18B20.getTempCByIndex(3));
    Serial.print(",");
    Serial.print(sensorDS18B20.getTempCByIndex(4));
    Serial.print(",");

    if (sensorDS18B20.getTempCByIndex(3) <= cutoffTemp) {
        // Turn relay on
        digitalWrite(pinRelayTemp, LOW);
        Serial.println("Prendido");
    } else {
        // Turn relay off
        digitalWrite(pinRelayTemp, HIGH);
        Serial.println("Apagado");
    }
    
    delay(loopTime);
}