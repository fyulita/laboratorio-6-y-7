#include <OneWire.h>
#include <DallasTemperature.h>

// Pin donde esta conectado DQ
const byte pinDatosDQ = 9;

OneWire ourWire(2);
DallasTemperature sensors(&ourWire);
//por referencia


void setup() {
  // Iniciamos la comunicación serie
  delay(1000);
  Serial.begin(9600);
  sensors.begin();
 
}

void loop() {
  sensors.requestTemperatures();
  float temp=sensors.getTempCByIndex(0);

  Serial.print(temp);
  Serial.println("");

  delay(1000);
}
