/**
 Sensors
 Name: sensors.ino
 Opdracht3:
 - Sensor data wordt continu gecapteerd met een interval van 250ms.
 - Je houd de laatste 10 metingen bij.

 @author Olivier Verhaegen
 @version 1.0.0
*/

#include <Wire.h>
#include <NewPing.h>

#define TRIG_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 200

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

uint8_t buffer[10];

void setup() {
  // Initialize Serial.
  Serial.begin(9600);
  
  // Initialize buffer
  for (byte i = 0; i < 10; i++) {
    buffer[i] = sonar.ping_cm();
  }
  
  // Initialize I2C on address 8.
  Wire.begin(8);
  Wire.onRequest(requestData);
  // Don't use internal pull ups
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);
}

void loop() {
  for (byte i = 0; i < 10; i++) {
    buffer[i] = sonar.ping_cm();
    delay(250);
  }
}

void requestData() {
  Serial.println("Master requested data.");
  Wire.write(buffer, 5);
}
