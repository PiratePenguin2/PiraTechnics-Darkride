#include <SoftwareSerial.h>

SoftwareSerial slaveSerial(2, 3); // RX, TX (for communication with the slave)

void setup() {
  Serial.begin(9600);      // Communication with the PC
  slaveSerial.begin(9600); // Communication with the slave
  Serial.println("Master ready...");
}

void loop() {
  // Send a command to the slave
  slaveSerial.println("Hello Slave!");

  // Check if there is a response from the slave
  if (slaveSerial.available()) {
    String response = slaveSerial.readStringUntil('\n');
    Serial.println("Slave says: " + response);
  }

  delay(1000); // Wait before sending the next message
}
 
