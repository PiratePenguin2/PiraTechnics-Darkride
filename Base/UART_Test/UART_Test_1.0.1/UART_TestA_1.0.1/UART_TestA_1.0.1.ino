//Master
#include <HardwareSerial.h>

HardwareSerial SerialPort(2); // use UART2

void setup()  
{
  SerialPort.begin(15200, SERIAL_8N1, 16, 17); 
  Serial.begin(9600);
} 

void loop()  
{ 
  // Send data to the slave
  SerialPort.print(1);
  Serial.println("Sent: 1");
  delay(1000);

  // Check if there is data from the slave
  if (SerialPort.available()) {
    char received = SerialPort.read();
    Serial.print("Received: ");
    Serial.println(received);
  }

  // Send data to the slave
  SerialPort.print(0);
  Serial.println("Sent: 0");
  delay(1000);

  // Check if there is data from the slave
  if (SerialPort.available()) {
    char received = SerialPort.read();
    Serial.print("Received: ");
    Serial.println(received);
  }
}
