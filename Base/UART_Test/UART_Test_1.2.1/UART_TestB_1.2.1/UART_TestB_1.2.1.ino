#include <Arduino.h>
#include <HardwareSerial.h>
HardwareSerial SerialPort(2);

const int Enable =  2;
const int SlaveNumber = 1;   // Change this for each slave
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
  if (SerialPort.available()) {
    if (SerialPort.read() == START_BYTE) {
      uint8_t slave_id = SerialPort.read();
      String command = SerialPort.readStringUntil(END_BYTE);
      uint8_t received_checksum = SerialPort.read();
      uint8_t calculated_checksum = slave_id + command.length();

      if (slave_id == SlaveNumber && received_checksum == calculated_checksum) {
        Serial.println("Message verified and is for this slave.");
        
        if (command == "ON") {
          digitalWrite(LED, HIGH);
          delay(500);  // Simulate task
          digitalWrite(LED, LOW);
        }

        // Send acknowledgment back in the correct format
        digitalWrite(Enable, HIGH);
        SerialPort.write(START_BYTE);
        SerialPort.print("ACK: ");
        SerialPort.print("Slave ");
        SerialPort.print(SlaveNumber);
        SerialPort.print(" ");
        SerialPort.print(command);
        SerialPort.write(END_BYTE);
        SerialPort.flush();
        digitalWrite(Enable, LOW);
        Serial.println("ACK sent to master.");
      }
    }
  }
}
