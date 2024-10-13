#include <SoftwareSerial.h>

SoftwareSerial masterSerial(2, 3); // RX, TX (for communication with the master)

void setup() {
  Serial.begin(9600);      // Communication with the PC
  masterSerial.begin(9600); // Communication with the master
  Serial.println("Slave ready...");
}

void loop() {
  // Check if there is a command from the master
  if (masterSerial.available()) {
    String command = masterSerial.readStringUntil('\n');
    Serial.println("Received command: " + command);

    // Respond to the master
    masterSerial.println("Acknowledged!");
  }

  delay(1000); // Wait before reading the next command
}
