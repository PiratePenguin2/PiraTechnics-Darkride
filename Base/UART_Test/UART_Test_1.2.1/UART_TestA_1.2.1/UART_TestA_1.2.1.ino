#include <Arduino.h>
#include <HardwareSerial.h>
HardwareSerial SerialPort(2);

const int BUTTON_PIN_01 = 13;
const int BUTTON_PIN_02 = 12;
const int Enable =  2;

// Message structure constants
const uint8_t START_BYTE = 0x7E;    // Start of message delimiter
const uint8_t END_BYTE = 0x7F;      // End of message delimiter

// Slave IDs
const uint8_t slave_1_id = 1;
const uint8_t slave_2_id = 2;

void setup() {
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
  pinMode(Enable, OUTPUT);
  digitalWrite(Enable, LOW);
  pinMode(BUTTON_PIN_01, INPUT_PULLUP);
  pinMode(BUTTON_PIN_02, INPUT_PULLUP);
  Serial.println("Started Sucsessfully!");
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

void loop() {
  if (digitalRead(BUTTON_PIN_01) == LOW) {
    delay(100);
    sendMessage(slave_1_id, "ON");
    Serial.println("Sent command to Slave 1");
  }

  if (digitalRead(BUTTON_PIN_02) == LOW) {
    delay(100);
    sendMessage(slave_2_id, "ON");
    Serial.println("Sent command to Slave 2");
  }

  if (SerialPort.available()) {
    String response = SerialPort.readStringUntil(END_BYTE);
    Serial.println("Received: " + response);
  }
  delay(100);
}
