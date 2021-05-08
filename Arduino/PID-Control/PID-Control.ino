// e(t) = r(t) - i(t)
// feedback(t) = Kp * e(t) + Ki * int(e(t), t) + Kd * D(e(t), t)   

// Import PIDController library
#include <PIDController.h>
PIDController pid;

// Define variables for the program.

// PID parameters
const double Kp = 5;
const double Ki = 0;
const double Kd = 1;

// Pins
const int ledPin = 9;  
const int sensorPin = 0;

// Signals
const int r = 72;
int lightLevel;
int feedback;

// Callibration parameters
const double a = 0;
const double b = 1;

void setup() {
  pinMode(ledPin, OUTPUT);  // LED
  
  Serial.begin(9600);       // Some methods require the Serial.begin() method to be called first.
  pid.begin();              // Initialize the PID instance.
  pid.setpoint(r);          // The "goal" the PID controller tries to "reach".
  pid.tune(Kp, Ki, Kd);     // Tune the PID, arguments: Kp, Ki, Kd.

  analogWrite(ledPin, 0);   // Initial perturbation.
}

void loop() {
  // Measure light level as a number between 0 (dark) and 255 (bright).
  lightLevel = analogRead(sensorPin); // Photoresistor, integer value between 0 and 1023.
  lightLevel = map(lightLevel, 0, 1023, 0, 255);

  lightLevel = callibration(a, b, lightLevel);

  Serial.println(F("Light level"));
  Serial.println(lightLevel);
  
  feedback = pid.compute(lightLevel);        // Let the PID compute the value, returns the optimal output.
  int newLightLevel = lightLevel + feedback;

  // Use signal to feed the LED.
  analogWrite(ledPin, newLightLevel);

  Serial.println(F("New light level"));
  Serial.println(newLightLevel);
  Serial.println(F("\n"));

  delay(1000);
}

int callibration(a, b, x) {
  int y = a + b * x;
  return y;
}
