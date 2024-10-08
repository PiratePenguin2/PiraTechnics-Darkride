#include <HardwareSerial.h>

#define MAX485_DE 4 // Define DE pin
#define MAX485_RE 5 // Define RE pin

HardwareSerial mySerial(1);

void setup() {
  Serial.begin(115200); // Start serial for debugging
  pinMode(MAX485_DE, OUTPUT);
  pinMode(MAX485_RE, OUTPUT);
  digitalWrite(MAX485_DE, LOW); // Set MAX485 to receive mode
  digitalWrite(MAX485_RE, LOW); // Set MAX485 to receive mode

  mySerial.begin(9600, SERIAL_8N1, 16, 17); // RX, TX pins
  Serial.println("Sender ESP32 ready.");
}

void loop() {
  digitalWrite(MAX485_DE, HIGH); // Set to transmit mode
  Serial.println("Sending message...");
  mySerial.println("Hello from Sender ESP32!");
  delay(10); // Small delay to ensure message is sent
  digitalWrite(MAX485_DE, LOW); // Set back to receive mode
  Serial.println("Switched to receive mode.");
  delay(1000); // Wait before sending the next message
}
