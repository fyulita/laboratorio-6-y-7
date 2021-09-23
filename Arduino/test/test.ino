unsigned long i = 65000;

void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.println(i);
    i = i + 1000;
    delay(1);
}
