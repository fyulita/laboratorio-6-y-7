// e(t) = r(t) - i(t)
// u(t) = Kp * e(t) + Ki * int(e(t), t) + Kd * D(e(t), t)   

// Import PIDController library
#include <PIDController.h>
PIDController pid;

// Define variables for the program.

// PID parameters
const int Kp = 1;
const int Ki = 1;
const int Kd = 1;

// Pins
const int ledPin = 9;  
const int sensorPin = 0;

// Signals
const int r = 112;
int lightLevel;
int u;

void setup() {
  pinMode(ledPin, OUTPUT);  // LED
  
  Serial.begin(9600);       // Some methods require the Serial.begin() method to be called first.
  pid.begin();              // Initialize the PID instance.
  pid.setpoint(r);          // The "goal" the PID controller tries to "reach".
  pid.tune(Kp, Ki, Kd);     // Tune the PID, arguments: Kp, Ki, Kd.
  pid.limit(0, 255);        // Limit the PID output between 0 and 255, this is important to get rid of integral windup!
}

void loop() {

  // Measure light level as a number between 0 (dark) and 255 (bright).
  lightLevel = analogRead(sensorPin); // Photoresistor, integer value between 0 and 1023.
  
  u = pid.compute(lightLevel);        // Let the PID compute the value, returns the optimal output.

  // Use signal to feed the LED.
  analogWrite(ledPin, u);

  Serial.println(u);

  delay(1000);
}
