// Define variables for the program.

// Pins
const int ledPin = 9;  
const int sensorPin = 0;

// Loop variables
int i = 0;       // Iterator
int lightLevel;
int lightArray[100];
int averageLightLevel;

void setup() {
  pinMode(ledPin, OUTPUT);    // LED
  pinMode(sensorPin, INPUT);  // Photoresistor

  Serial.begin(9600);
  
  analogWrite(ledPin, 225);
}

void loop() {
  lightLevel = analogRead(sensorPin);
  lightLevel = map(lightLevel, 0, 1023, 0, 255);

  if(i < 100){
    lightArray[i] = lightLevel;
    i++;
  } else if(i == 100){
    averageLightLevel = average(lightArray, 100);
    Serial.println(averageLightLevel);
    i++;
  }
  
  delay(10);
}

int average(int a[], int len) {
  int total = 0;
  for(int j = 0; j < len; j++) {
    total = total + a[j];
  }

  int ans = (int)total / (int)len;
  return ans;
}

/* ## Results ##
 *  
 *  x = [000, 025, 050, 075, 100, 125, 150, 175, 200, 225, 255]
 *  y = [254, 177, 141, 120, 104, 096, 087, 081, 075, 072, 066]
 */
