//Slave
#include <HardwareSerial.h>

HardwareSerial SerialPort(2); // use UART2

void setup()
{
  SerialPort.begin(15200, SERIAL_8N1, 16, 17);
  Serial.begin(9600);
}

void loop()
{
  if (SerialPort.available())
  {
    char number = SerialPort.read();
    Serial.print("Received: ");
    Serial.println(number);

    // Send a response back to the master based on the received number
    if (number == '0') {
      SerialPort.print('0');  // Respond back
      Serial.println("Sent: 0");
    }
    if (number == '1') {
      SerialPort.print('1');  // Respond back
      Serial.println("Sent: 1");
    }
  }
}
