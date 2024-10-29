#include <Arduino.h>
#include <HardwareSerial.h>
HardwareSerial SerialPort(2);

const int Enable = 2;
const int SlaveNumber = 1;  // Change this for each slave
const int LED = 4;

// Message structure constants
const uint8_t START_BYTE = 0x7E;
const uint8_t END_BYTE = 0x7F;

void setup() {
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
  pinMode(Enable, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(Enable, LOW);
  digitalWrite(LED, LOW);
}

void loop() {
  static String messageBuffer;  // Buffer for accumulating the message
  bool messageComplete = false;

  // Check if data is available in the SerialPort
  while (SerialPort.available()) {
    char incomingByte = SerialPort.read();

    // Log every byte seen by the slave
    Serial.print("Received byte: ");
    Serial.println(incomingByte, HEX);

    // Detect start of message
    if (incomingByte == START_BYTE) {
      messageBuffer = "";  // Clear buffer for new message
      messageBuffer += incomingByte;
    } 
    // Detect end of message
    else if (incomingByte == END_BYTE) {
      messageBuffer += incomingByte;
      messageComplete = true; // Mark message as complete
    } 
    // Accumulate bytes in buffer
    else {
      messageBuffer += incomingByte;
    }

    // When a complete message is detected, parse it
    if (messageComplete) {
      Serial.println("Full message received: " + messageBuffer);

      // Parse the message only if it starts with the start byte and has a valid structure
      if (messageBuffer[0] == START_BYTE) {
        uint8_t slave_id = messageBuffer[1];
        String command = messageBuffer.substring(2, messageBuffer.length() - 2);
        uint8_t received_checksum = messageBuffer[messageBuffer.length() - 2];
        uint8_t calculated_checksum = slave_id + command.length();

        // Log the decoded message details
        Serial.print("Decoded Slave ID: ");
        Serial.println(slave_id);
        Serial.print("Decoded Command: ");
        Serial.println(command);
        Serial.print("Received Checksum: ");
        Serial.println(received_checksum, HEX);
        Serial.print("Calculated Checksum: ");
        Serial.println(calculated_checksum, HEX);

        // Check if the message is intended for this slave and if the checksum matches
        if (slave_id == SlaveNumber && received_checksum == calculated_checksum) {
          Serial.println("Message verified and is for this slave.");

          if (command == "ON") {
            digitalWrite(LED, HIGH);
            delay(500);  // Simulate task
            digitalWrite(LED, LOW);
          } else if (command == "OFF") {
            digitalWrite(LED, LOW);
          }

          // Send acknowledgment
          digitalWrite(Enable, HIGH);
          SerialPort.write(START_BYTE);
          SerialPort.print("ACK: Slave ");
          SerialPort.print(SlaveNumber);
          SerialPort.print(" ");
          SerialPort.print(command);
          SerialPort.write(END_BYTE);
          SerialPort.flush();
          digitalWrite(Enable, LOW);

        } else {
          Serial.println("Message checksum invalid or not intended for this slave.");
        }
      }
      
      // Reset message buffer and flag for next message
      messageBuffer = "";
      messageComplete = false;
    }
  }
}
