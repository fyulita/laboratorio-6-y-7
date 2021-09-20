
const int pinRelay = 8;


void setup() {
    Serial.begin(9600);
    //Para el relay:
    pinMode(pinRelay, OUTPUT); //conexión a S del relay
}
 

void loop() {
    digitalWrite(pinRelay, HIGH); //turn relay ON
    Serial.println("Prendido");
    delay(10000);
    digitalWrite(pinRelay, LOW);//turn relay OFF
    Serial.println("Apagado");
    delay(5000); 
}
