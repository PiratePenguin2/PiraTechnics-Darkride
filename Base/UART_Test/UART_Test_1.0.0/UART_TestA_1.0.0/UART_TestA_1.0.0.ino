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
  SerialPort.print(1);
  Serial.println("1");
  delay(1000);
  SerialPort.print(0);
  Serial.println("0");
  delay(1000);
}