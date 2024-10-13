#include <Stepper.h>

const int stepsPerRevolution = 2048;  // steps per revolution for the 28BYJ-48

// Define the pins connected to the ULN2003 driver
const int motorPin1 = 26; 
const int motorPin2 = 25; 
const int motorPin3 = 27; 
const int motorPin4 = 14; 

// Create a Stepper object
Stepper myStepper(stepsPerRevolution, motorPin1, motorPin2, motorPin3, motorPin4);

void setup() {
  myStepper.setSpeed(30); // Increase speed for better torque
  Serial.begin(9600);
}

void loop() {
  Serial.println("Rotating clockwise");
  myStepper.step(2048); // Move 100 steps clockwise
  delay(1000); // Wait for a second

  Serial.println("Rotating counterclockwise");
  myStepper.step(-2048); // Move 100 steps counterclockwise
  delay(1000); // Wait for a second
}
