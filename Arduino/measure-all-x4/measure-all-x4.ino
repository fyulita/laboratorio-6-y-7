#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <MHZ19.h>
#include <SoftwareSerial.h>


#define baudrate 9600
#define pinDatosDQ 2
#define pinRelayTemp 3
#define pinRelayValvula_1 4
#define pinRelayValvula_2 5
#define pinRelayValvula_3 6
#define pinRelayValvula_4 7
#define pinRx 12
#define pinTx 13


// Constructors
OneWire myOneWire(pinDatosDQ);
DallasTemperature sensorDS18B20(&myOneWire);
MHZ19 myMHZ19;
SoftwareSerial mySerial(pinRx, pinTx);


// Time intervals

//#define co2Time 1800000 // 30 mins.
#define co2Time 300000    // 30 mins.

const int loopTime = 5000;
unsigned long currentTime = 0;
unsigned long previousTime = 0;


// Which CO2 sensor is being used. 0 means the sensor isn't being used.
int useSensor = 1;


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
    pinMode(pinRelayValvula_1, OUTPUT);
    pinMode(pinRelayValvula_2, OUTPUT);
    pinMode(pinRelayValvula_3, OUTPUT);
    pinMode(pinRelayValvula_4, OUTPUT);

    // Calibrate CO2 sensor
    myMHZ19.autoCalibration();

    // Initialize valves
    digitalWrite(pinRelayValvula_1, HIGH);
    digitalWrite(pinRelayValvula_2, LOW);
    digitalWrite(pinRelayValvula_3, LOW);
    digitalWrite(pinRelayValvula_4, LOW);
}

 
void loop() {
    // CO2 sensor
    Serial.print(myMHZ19.getCO2());
    Serial.print(",");

    // millis() can run without an overflow for up to 5 months
    currentTime = millis();

    for (int i = 1; i <= 4; i++) {
        if (i == useSensor) {
            // CO2 valve
            Serial.print("Prendido");
            Serial.print(",");
        } else {
            // CO2 valve
            Serial.print("Apagado");
            Serial.print(",");
        }
    }

    if (currentTime - previousTime >= co2Time) {
        previousTime = currentTime;
        
        if (useSensor == 1) {
            // Turn CO2 valve 1 off
            digitalWrite(pinRelayValvula_1, LOW);
            // Turn CO2 valve 2 on
            digitalWrite(pinRelayValvula_2, HIGH);
            
            useSensor = 2;
        } else if (useSensor == 2) {
            // Turn CO2 valve 2 off
            digitalWrite(pinRelayValvula_2, LOW);
            // Turn CO2 valve 3 on
            digitalWrite(pinRelayValvula_3, HIGH);
            
            useSensor = 3;
        } else if (useSensor == 3) {
            // Turn CO2 valve 3 off
            digitalWrite(pinRelayValvula_3, LOW);
            // Turn CO2 valve 4 on
            digitalWrite(pinRelayValvula_4, HIGH);
            
            useSensor = 4;
        } else {
            // Turn CO2 valve 4 off
            digitalWrite(pinRelayValvula_4, LOW);
            // Turn CO2 valve 1 on
            digitalWrite(pinRelayValvula_1, HIGH);

            useSensor = 1;
        }
    }

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
