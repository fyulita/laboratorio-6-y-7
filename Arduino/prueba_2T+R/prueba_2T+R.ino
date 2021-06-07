#include <OneWire.h>
#include <DallasTemperature.h>

// Pin donde se conecta el bus 1-Wire
const int pinDatosDQ = 2;

// Instancia a las clases OneWire y DallasTemperature
OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);
 
void setup() {
    // Iniciamos la comunicación serie
    Serial.begin(9600);
    // Iniciamos el bus 1-Wire
    sensorDS18B20.begin(); 

    //Para el relay:
    pinMode(7, OUTPUT); //conexión a S del relay
}
 
void loop() {
    // CODIGO PARA EL SENSOR
    sensorDS18B20.requestTemperatures();
    // Leemos y mostramos los datos de los sensores DS18B20
    Serial.print(sensorDS18B20.getTempCByIndex(0));
    Serial.print(" , ");
    Serial.print(sensorDS18B20.getTempCByIndex(1));
    Serial.print(" , ");


    if(sensorDS18B20.getTempCByIndex(1)<=20){
      digitalWrite(7,HIGH); //turn relay ON
      Serial.println("Prendido");
    }
    else{
      digitalWrite(7,LOW); //turn relay OFF
      Serial.println("Apagado");
    }
    
    delay(1000); 

    
}
