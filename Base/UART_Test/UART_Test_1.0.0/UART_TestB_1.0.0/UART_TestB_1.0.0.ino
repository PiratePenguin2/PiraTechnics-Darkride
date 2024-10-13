//Slave
#include <HardwareSerial.h>

HardwareSerial SerialPort(2); // use UART2


char number  = ' ';
int LED = 15;

void setup()
{
  SerialPort.begin(15200, SERIAL_8N1, 16, 17);
  //pinMode(LED, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  if (SerialPort.available())
  {
    char number = SerialPort.read();
    if (number == '0') {
      //digitalWrite(LED, LOW);
      Serial.println("0");
    }
    if (number == '1') {
      //digitalWrite(LED, HIGH);
      Serial.println("1");
    }
  }
}