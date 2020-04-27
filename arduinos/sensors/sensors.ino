/**
 Sensors
 Name: sensors.ino
 Purpose: This Arduino nano is used for reading and handeling the sensor values.

 @author Olivier Verhaegen
 @version 1.0.0
*/

#include <Wire.h>

void setup() {
  // Initialize I2C on address 8.
  Wire.begin(8);
  Wire.onReceive(receiveData);
  Wire.onRequest(requestData);
  // Don't use internal pull ups
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);

  // Initialize Serial.
  Serial.begin(9600);
}

void loop() {

}

void receiveData(int numOfBytes) {
  while(Wire.available() > 0) {
    byte dataByte = Wire.read();
    printReceivedData(dataByte);
  }

  // Read as int.
  // int dataInt = Wire.read();
  // printReceivedData(dataInt);
}

void requestData() {
  Serial.println("Master requested data.");
  uint8_t buffer[3];
  buffer[0] = 1;
  buffer[1] = 2;
  buffer[2] = 3;
  Wire.write(buffer, 3);
}

void printReceivedData(int data) {
  Serial.print("Received data: ");
  Serial.println(data);
}
