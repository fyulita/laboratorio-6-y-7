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
