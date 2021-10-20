#define valvula1 6
#define valvula2 7

void setup() {
    pinMode(valvula1, OUTPUT);
    pinMode(valvula2, OUTPUT);
}

void loop() {
    digitalWrite(valvula1, HIGH);
    digitalWrite(valvula2, LOW);
    delay(5000);
    digitalWrite(valvula1, LOW);
    digitalWrite(valvula2, HIGH);
    delay(5000);
}
