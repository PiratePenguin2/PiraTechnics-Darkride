#include <AccelStepper.h>

// Define the stepper motor and the pins connected to the A4988 driver
// Parameters: (1, STEP_PIN, DIR_PIN)
AccelStepper stepper1(AccelStepper::DRIVER, 2, 5); // A4988 driver for motor 1
AccelStepper stepper2(AccelStepper::DRIVER, 3, 6); // A4988 driver for motor 2

void setup() {
  // Configure stepper 1
  stepper1.setMaxSpeed(1000);         // Set maximum speed (steps per second)
  stepper1.setAcceleration(500);      // Set acceleration (steps per second^2)
  stepper1.setCurrentPosition(0);     // Initialize the current position to 0

  // Configure stepper 2
  stepper2.setMaxSpeed(1000);
  stepper2.setAcceleration(500);
  stepper2.setCurrentPosition(0);
}

void loop() {
  // Move motor 1 to position 800 steps
  stepper1.moveTo(800);               // Move to 800 steps (one rotation for 28BYJ-48 in full-step mode)
  stepper1.runToPosition();           // Block until motor 1 reaches its target

  // Move motor 2 to position 1600 steps (double the distance)
  stepper2.moveTo(1600);
  stepper2.runToPosition();

  // Now move both steppers back to position 0
  stepper1.moveTo(0);                 // Set target back to 0
  stepper2.moveTo(0);
  
  // Non-blocking run: both motors move at the same time back to 0
  while (stepper1.currentPosition() != 0 || stepper2.currentPosition() != 0) {
    stepper1.run();                   // Non-blocking movement for motor 1
    stepper2.run();                   // Non-blocking movement for motor 2
  }
}
