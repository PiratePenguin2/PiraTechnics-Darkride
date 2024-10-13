//Master
#include <HardwareSerial.h>

HardwareSerial SerialPort(2); // use UART2

const int DE_PIN = 4; // Driver Enable pin
const int RE_PIN = 5; // Receive Enable pin

void setup()  
{
  SerialPort.begin(15200, SERIAL_8N1, 16, 17); 
  Serial.begin(9600);
  
  pinMode(DE_PIN, OUTPUT);
  pinMode(RE_PIN, OUTPUT);
  
  digitalWrite(DE_PIN, LOW); // Set to receive mode
  digitalWrite(RE_PIN, LOW); // Set to receive mode
} 

void loop()  
{ 
  // Send data to the slave
  digitalWrite(DE_PIN, HIGH); // Set to transmit mode
  digitalWrite(RE_PIN, HIGH);  // Set to transmit mode
  
  SerialPort.print(1);
  Serial.println("Sent: 1");
  delay(10); // Short delay to allow transmission to complete
  
  // Switch to receive mode
  digitalWrite(DE_PIN, LOW);
  digitalWrite(RE_PIN, LOW);
  delay(1000); // Wait for slave response

  // Check if there is data from the slave
  if (SerialPort.available()) {
    char received = SerialPort.read();
    Serial.print("Received: ");
    Serial.println(received);
  }

  // Send data to the slave
  digitalWrite(DE_PIN, HIGH); // Set to transmit mode
  digitalWrite(RE_PIN, HIGH);  // Set to transmit mode
  
  SerialPort.print(0);
  Serial.println("Sent: 0");
  delay(10); // Short delay to allow transmission to complete

  // Switch to receive mode
  digitalWrite(DE_PIN, LOW);
  digitalWrite(RE_PIN, LOW);
  delay(1000); // Wait for slave response

  // Check if there is data from the slave
  if (SerialPort.available()) {
    char received = SerialPort.read();
    Serial.print("Received: ");
    Serial.println(received);
  }
}
