#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <MHZ19.h>
#include <SoftwareSerial.h>


#define baudrate 9600
#define pinDatosDQ 2
#define pinRelayTemp 7
#define pinRelayValvulaCO2 8
#define pinRelayValvulaCompost 9
#define pinRx 10
#define pinTx 11


// Constructors
OneWire myOneWire(pinDatosDQ);
DallasTemperature sensorDS18B20(&myOneWire);
MHZ19 myMHZ19;
SoftwareSerial mySerial(pinRx, pinTx);


// Time intervals
const unsigned int compostTime = 10 * 60 * 1000;
const unsigned int co2Time = 10 * 60 * 1000;
const unsigned int loopTime = 5 * 1000;
unsigned long currentTime = 0;
unsigned long previousTime = 0;


// Whether the CO2 sensor is being used.
int useSensor = 0;


void setup() {
    Serial.begin(baudrate);
    mySerial.begin(baudrate);

    sensorDS18B20.begin(); 
    myMHZ19.begin(mySerial);

    // Relay pins
    pinMode(pinRelayTemp, OUTPUT);
    pinMode(pinRelayValvulaCO2, OUTPUT);
    pinMode(pinRelayValvulaCompost, OUTPUT);

    myMHZ19.autoCalibration();
}
 
void loop() {
    // CO2 sensor
    Serial.println(myMHZ19.getCO2());
    Serial.print(",");

    currentTime = millis();

    if (useSensor == 0) {
        // CO2 valve
        Serial.println("Prendido");
        Serial.print(",");
        // Compost valve
        Serial.println("Apagado");
        Serial.print(",");

        if (currentTime - previousTime >= compostTime) {
            useSensor = 1;
            previousTime = currentTime;

            // Turn CO2 valve on                       
            digitalWrite(pinRelayValvulaCO2, HIGH);
            digitalWrite(pinRelayValvulaCompost, LOW);
        }
    } else {
        // CO2 valve
        Serial.println("Apagado");
        Serial.print(",");
        // Compost valve
        Serial.println("Prendido");
        Serial.print(",");
                                                         
        if (currentTime - previousTime >= co2Time) {
            useSensor = 0;
            previousTime = currentTime;
                                                         
            // Turn CO2 valve on                       
            digitalWrite(pinRelayValvulaCompost, HIGH);
            digitalWrite(pinRelayValvulaCO2, LOW);
        }
    }

    // Temperature sensors
    sensorDS18B20.requestTemperatures();
    Serial.print(sensorDS18B20.getTempCByIndex(0));
    Serial.print(",");
    Serial.print(sensorDS18B20.getTempCByIndex(1));
    Serial.print(",");


    if (sensorDS18B20.getTempCByIndex(1) <= 55) {
        // Turn relay on
        digitalWrite(pinRelay, HIGH);
        Serial.println("Prendido");
    } else {
        // Turn relay off
        digitalWrite(pinRelay, LOW);
        Serial.println("Apagado");
    }
    
    delay(loopTime);
}
