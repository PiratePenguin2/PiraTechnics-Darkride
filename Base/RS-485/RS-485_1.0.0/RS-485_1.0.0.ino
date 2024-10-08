#define MAX485_DE_RE 4  // Pin to control DE and RE (TX and RX mode)
#define TX_PIN 17       // ESP32 TX pin
#define RX_PIN 16       // ESP32 RX pin

void setup() {
  Serial.begin(115200);    // Serial Monitor for debugging
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);  // Use Serial2 for communication with MAX485

  pinMode(MAX485_DE_RE, OUTPUT);
  digitalWrite(MAX485_DE_RE, LOW);  // Set to receive mode

  Serial.println("MAX485 Loopback Test Initialized");
}

void loop() {
  // Transmit Mode
  digitalWrite(MAX485_DE_RE, HIGH);  // Enable transmit
  Serial2.write("Hello, MAX485");
  Serial.println("Sent: Hello, MAX485");
  delay(1000);

  // Receive Mode
  digitalWrite(MAX485_DE_RE, LOW);  // Enable receive
  delay(100);  // Allow time for response

  while (Serial2.available()) {
    char receivedChar = Serial2.read();
    Serial.print("Received: ");
    Serial.println(receivedChar);
  }

  delay(2000);
}
