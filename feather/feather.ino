/**
 Adafruit HUZZAH32 - ESP32 Feather
 Name: feather.ino
 Purpose: This controller is used to handle communication between the arduino's and the internet using MQTT and I²C.

 @author Olivier Verhaegen
 @version 1.0.0
*/

// https://forum.arduino.cc/index.php?topic=167162.0

#include <Wire.h>

#define MOTOR_I2C 4
#define SENSOR_I2C 8

byte x = 0;

void setup() {
  // Initialize I2C bus (address optional for master).
  Wire.begin();

  // Initialize Serial.
  Serial.begin(9600);
}

void loop() {
  // Write data
  Wire.beginTransmission(MOTOR_I2C);
  Wire.write(x);
  Serial.print("Writing to motors: ");
  Serial.println(x);
  Wire.endTransmission();

  Wire.beginTransmission(SENSOR_I2C);
  Wire.write(x);
  Serial.print("Writing to sensors: ");
  Serial.println(x);
  Wire.endTransmission();

  x++;

  // Read data
  Wire.requestFrom(MOTOR_I2C, 3);
  while(Wire.available()) {
    byte a = Wire.read();
    Serial.println(a);
  }
  // for(int i=0; i < 3; i++) {
  //   byte a = Wire.read();
  //   Serial.println(a);
  // }

  Wire.requestFrom(SENSOR_I2C, 3);
  while(Wire.available()) {
    byte a = Wire.read();
    Serial.println(a);
  }
  // for(int i=0; i < 3; i++) {
  //   byte a = Wire.read();
  //   Serial.println(a);
  // }

  delay(500);
}
