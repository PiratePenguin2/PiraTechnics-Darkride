#include <Arduino.h>
#include <string.h>
#include <HardwareSerial.h>
HardwareSerial SerialPort(2);

int slave_1_id = 1;
int slave_2_id = 2;

const int BUTTON_PIN_01 = 12;
const int BUTTON_PIN_02 = 13;
const int Enable =  2;

void setup() {
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17); 
  //SerialPort.setTimeout(250);
  pinMode(Enable, OUTPUT);
  digitalWrite(Enable, LOW);
  pinMode(BUTTON_PIN_01, INPUT_PULLUP);
  pinMode(BUTTON_PIN_02, INPUT_PULLUP);
}

void loop() {
     /* Master Program  */
     if(digitalRead(BUTTON_PIN_01) == 0){
      delay(100);
      digitalWrite(Enable, HIGH);
      SerialPort.print(slave_1_id);
      SerialPort.print("ON");
      SerialPort.flush();
      digitalWrite(Enable, LOW);
      Serial.println("1 Push");
      //digitalWrite(BUTTON_PIN_01, HIGH);
     }
      
      
      if(digitalRead(BUTTON_PIN_02) == 0){
        delay(100);
        digitalWrite(Enable, HIGH);
        SerialPort.print(slave_2_id);
        SerialPort.print("ON");
        SerialPort.flush();
        digitalWrite(Enable, LOW); 
        Serial.println("2 Push");
      }

      if(SerialPort.available()){
        Serial.println(SerialPort.readString());
      }
      delay(100);
      
  }