#include <HardwareSerial.h>

#define MAX485_DE 4 // Define DE and RE pin
#define MAX485_RE 5

HardwareSerial mySerial(1);

void setup() {
  Serial.begin(115200); // Start serial for debugging
  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_DE, LOW); // Set MAX485 to receive mode

  mySerial.begin(9600, SERIAL_8N1, 16, 17); // RX, TX pins
  Serial.println("Receiver ESP32 ready.");
}

void loop() {
  if (mySerial.available()) {
    digitalWrite(MAX485_DE, LOW); // Ensure we are in receive mode
    String message = mySerial.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(message);
  } else {
    Serial.println("Waiting for message...");
  }
  delay(500); // Reduce frequency of checking for messages
}
