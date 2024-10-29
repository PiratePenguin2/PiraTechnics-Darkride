#include <HardwareSerial.h>
HardwareSerial SerialPort(2);
const int Enable =  2;
const int SlaveNumber = 1;
int Slave;
const int LED = 4;
void setup() 
{ 
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17); 
  SerialPort.setTimeout(250);
  pinMode(Enable, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(Enable, LOW);
  digitalWrite(LED, LOW);
} 
void loop() 
{
  digitalWrite(Enable, LOW); 
  if(SerialPort.available())
  {
      Slave = SerialPort.parseInt();
      Serial.println(Slave);
      if(Slave == SlaveNumber)
      {   
        String command = SerialPort.readString();  
          Serial.println(command);
           if(command == "ON")
           {
              //digitalWrite(LED, HIGH);
              //Serial.println("HIGH");
              delay(500);
              //digitalWrite(LED, LOW);
              //Serial.println("LOW");
            }
              digitalWrite(Enable, HIGH);
              SerialPort.println("Slave 1 is triggered");   
           }
           //Serial.println("loop");/
        }   
    }