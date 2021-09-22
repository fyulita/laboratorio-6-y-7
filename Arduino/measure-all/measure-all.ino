#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <MHZ19.h>
#include <SoftwareSerial.h>


#define baudrate 9600
#define pinDatosDQ 2
#define pinRelayTemp 7
#define pinRelayValvulaCO2 4
#define pinRelayValvulaCompost 5
#define pinRx 10
#define pinTx 11


// Constructors
OneWire myOneWire(pinDatosDQ);
DallasTemperature sensorDS18B20(&myOneWire);
MHZ19 myMHZ19;
SoftwareSerial mySerial(pinRx, pinTx);


// Time intervals
#define compostTime 120000 // 2 mins.
#define co2Time 120000 // 2 mins.
const int loopTime = 5000;
unsigned long currentTime = 0;
unsigned long previousTime = 0;


// Whether the CO2 sensor is being used.
bool useSensor = false;


// Cutoff temperature for the compost
const unsigned int cutoffTemp = 55;


void setup() {
    // Serials
    Serial.begin(baudrate);
    mySerial.begin(baudrate);

    sensorDS18B20.begin(); 
    myMHZ19.begin(mySerial);

    // Relay pins
    pinMode(pinRelayTemp, OUTPUT);
    pinMode(pinRelayValvulaCO2, OUTPUT);
    pinMode(pinRelayValvulaCompost, OUTPUT);

    // Calibrate CO2 sensor
    myMHZ19.autoCalibration();

    // Initialize valves
    digitalWrite(pinRelayValvulaCO2, HIGH);
    digitalWrite(pinRelayValvulaCompost, LOW);
}

 
void loop() {
    // CO2 sensor
    Serial.print(myMHZ19.getCO2());
    Serial.print(",");

    // millis() can run without an overflow for up to 5 months
    currentTime = millis();

    if (useSensor) {
        // CO2 valve
        Serial.print("Prendido");
        Serial.print(",");
        // Compost valve
        Serial.print("Apagado");
        Serial.print(",");

        if (currentTime - previousTime >= co2Time) {
            useSensor = false;
            previousTime = currentTime;

            // Turn CO2 valve off                       
            digitalWrite(pinRelayValvulaCompost, HIGH);
            digitalWrite(pinRelayValvulaCO2, LOW);
        }
    } else {
        // CO2 valve
        Serial.print("Apagado");
        Serial.print(",");
        // Compost valve
        Serial.print("Prendido");
        Serial.print(",");
                                                         
        if (currentTime - previousTime >= compostTime) {
            useSensor = true;
            previousTime = currentTime;
                                                         
            // Turn CO2 valve on                       
            digitalWrite(pinRelayValvulaCO2, HIGH);
            digitalWrite(pinRelayValvulaCompost, LOW);
        }
    }

    // Temperature sensors
    sensorDS18B20.requestTemperatures();
    Serial.print(sensorDS18B20.getTempCByIndex(0));
    Serial.print(",");
    Serial.print(sensorDS18B20.getTempCByIndex(1));
    Serial.print(",");

    if (sensorDS18B20.getTempCByIndex(1) <= cutoffTemp) {
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
