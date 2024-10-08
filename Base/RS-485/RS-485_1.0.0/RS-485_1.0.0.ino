#define DE_PIN 4   // GPIO for Driver Enable
#define RE_PIN 5   // GPIO for Receiver Enable

void setup() {
  // Start Serial for debugging
  Serial.begin(115200);
  Serial.println("Main Serial Started");
  
  // Start the RS-485 serial communication (9600 baud)
  Serial2.begin(9600, SERIAL_8N1, 16, 17);  // RX = GPIO16, TX = GPIO17
  
  // Set DE/RE pins as outputs
  pinMode(DE_PIN, OUTPUT);
  pinMode(RE_PIN, OUTPUT);
  
  // Start in receive mode
  digitalWrite(DE_PIN, LOW);
  digitalWrite(RE_PIN, LOW);
}

void loop() {
  // Send data over RS-485
  digitalWrite(DE_PIN, HIGH);  // Enable transmitter
  digitalWrite(RE_PIN, HIGH);  // Disable receiver
  
  // Use Serial2.write to send raw data as bytes
  const char* message = "Hello, RS-485!";
  Serial2.write(message, strlen(message));  // Send the message over RS-485
  delay(10);
  
  // Switch to receive mode
  digitalWrite(DE_PIN, LOW);  // Disable transmitter
  digitalWrite(RE_PIN, LOW);  // Enable receiver
  
  // Receive data
  if (Serial2.available()) {
    String received = Serial2.readString();
    Serial.println("Received: " + received);
  }
  
  delay(1000);  // Wait for a second before sending again
}
