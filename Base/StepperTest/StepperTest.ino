#include <AccelStepper.h>

// Define pin numbers for stepper motor control
#define DIR_PIN  18  // GPIO for direction
#define STEP_PIN 19  // GPIO for step

// Create an instance of the AccelStepper class
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Set maximum speed and acceleration
  stepper.setMaxSpeed(1000);      // Set max speed (steps per second)
  stepper.setAcceleration(500);    // Set acceleration (steps per second^2)

  // Move to the starting position
  stepper.moveTo(1000); // Move 1000 steps forward
  Serial.println("Moving to position 1000");
}

void loop() {
  // Move to the target position
  if (stepper.distanceToGo() == 0) {
    // If reached the target position, reverse direction
    if (stepper.currentPosition() == 1000) {
      stepper.moveTo(0); // Move back to the start
      Serial.println("Moving to position 0");
    } else {
      stepper.moveTo(1000); // Move back to the end
      Serial.println("Moving to position 1000");
    }
  }

  // Call the run method to keep the motor moving
  stepper.run();

  // Debug output: Print the current position
  Serial.print("Current Position: ");
  Serial.println(stepper.currentPosition());
}
