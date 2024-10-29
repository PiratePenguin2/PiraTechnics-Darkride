#include <Arduino.h>
#include <HardwareSerial.h>
HardwareSerial SerialPort(2);

const int BUTTON_PIN_01 = 13;
const int BUTTON_PIN_02 = 12;
const int Enable = 2;

// Message structure constants
const uint8_t START_BYTE = 0x7E;  // Start of message delimiter
const uint8_t END_BYTE = 0x7F;    // End of message delimiter

// Slave IDs
const uint8_t slave_1_id = 1;
const uint8_t slave_2_id = 2;

// Acknowledgment settings
const unsigned long ACK_TIMEOUT = 500;  // Timeout period in milliseconds

void setup() {
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
  pinMode(Enable, OUTPUT);
  digitalWrite(Enable, LOW);
  pinMode(BUTTON_PIN_01, INPUT_PULLUP);
  pinMode(BUTTON_PIN_02, INPUT_PULLUP);
  Serial.println("Started Successfully!");
}

// Helper function to send a structured message
void sendMessage(uint8_t slave_id, const char* command) {
  digitalWrite(Enable, HIGH);
  SerialPort.write(START_BYTE);               // Start delimiter
  SerialPort.write(slave_id);                 // Slave ID
  SerialPort.write(command);                  // Command (e.g., "ON" or "OFF")
  uint8_t checksum = slave_id + strlen(command);
  SerialPort.write(checksum);                 // Checksum for error checking
  SerialPort.write(END_BYTE);                 // End delimiter
  SerialPort.flush();
  digitalWrite(Enable, LOW);
}

// Function to wait for acknowledgment
bool waitForAck(uint8_t slave_id) {
  unsigned long startTime = millis();
  while (millis() - startTime < ACK_TIMEOUT) {
    if (SerialPort.available()) {
      String response = SerialPort.readStringUntil(END_BYTE);
      Serial.println("Received: " + response);

      // Check if the response is an acknowledgment from the correct slave
      if (response.startsWith("ACK:") && response.indexOf(String(slave_id)) != -1) {
        Serial.println("Acknowledgment received from Slave " + String(slave_id));
        return true;  // ACK received, message successful
      }
    }
  }
  Serial.println("No acknowledgment received from Slave " + String(slave_id));
  return false;  // No ACK received, message failed
}

void loop() {
  // Check button press for Slave 1
  if (digitalRead(BUTTON_PIN_01) == LOW) {
    delay(100);  // Debounce delay
    sendMessage(slave_1_id, "ON");
    Serial.println("Sent command to Slave 1");

    // Wait for acknowledgment
    if (waitForAck(slave_1_id)) {
      Serial.println("Command to Slave 1 was successful");
    } else {
      Serial.println("Failed to communicate with Slave 1");
    }
  }

  // Check button press for Slave 2
  if (digitalRead(BUTTON_PIN_02) == LOW) {
    delay(100);  // Debounce delay
    sendMessage(slave_2_id, "ON");
    Serial.println("Sent command to Slave 2");

    // Wait for acknowledgment
    if (waitForAck(slave_2_id)) {
      Serial.println("Command to Slave 2 was successful");
    } else {
      Serial.println("Failed to communicate with Slave 2");
    }
  }

  delay(100);
}
