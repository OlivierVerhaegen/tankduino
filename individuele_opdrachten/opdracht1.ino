/**
 Opdracht 1
 Name: opdracht1.ino
 Purpose: Test basic functionality of the SN754410NE H-bridge IC.

 @author Olivier Verhaegen
 @version 1.0.0
*/

#define L_FWD 9
#define L_BWD 8
#define R_FWD 2
#define R_BWD 3
#define EN_L 6
#define EN_R 5

byte outputs[] = {L_FWD, L_BWD, R_FWD, R_BWD, EN_L, EN_R};

void setup() {
  // Initialize Outputs.
  for (byte i = 0; i < sizeof(outputs); i++) {
    pinMode(outputs[i], OUTPUT);
  }
  pinMode(LED_BUILTIN, OUTPUT);
  

  // Initialize Serial.
  Serial.begin(9600);
}

void loop() {
  stopMotors();
  // Start indication.
  for (byte i = 0; i < 25; i++) {
    if(i % 2 == 0) {
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
    delay(200);
    Serial.println("Starting ...");
  }
  

  // 5 seconden vooruit rijden.
  driveForward();
  delay(5000);

  // 360 graden rond eigen as draaien.
  rotateLeft();
  delay(7800);

  // 5 seconden achteruit rijden.
  driveBackward();
  delay(5000);

  // 180 graden rond eigen as rechts draaien.
  rotateRight();
  delay(3900);
}

void stopMotors() {
  for (byte i = 0; i < sizeof(outputs); i++) {
    digitalWrite(outputs[i], LOW);
  }
}

void enableMotors() {
  digitalWrite(EN_L, HIGH);
  digitalWrite(EN_R, HIGH);
}

void driveForward() {
  enableMotors();
  digitalWrite(L_FWD, HIGH);
  digitalWrite(L_BWD, LOW);
  digitalWrite(R_FWD, HIGH);
  digitalWrite(R_BWD, LOW);
}

void driveBackward() {
  enableMotors();
  digitalWrite(L_FWD, LOW);
  digitalWrite(L_BWD, HIGH);
  digitalWrite(R_FWD, LOW);
  digitalWrite(R_BWD, HIGH);
}

void rotateLeft() {
  enableMotors();
  digitalWrite(L_FWD, LOW);
  digitalWrite(L_BWD, HIGH);
  digitalWrite(R_FWD, HIGH);
  digitalWrite(R_BWD, LOW);
}

void rotateRight() {
  enableMotors();
  digitalWrite(L_FWD, HIGH);
  digitalWrite(L_BWD, LOW);
  digitalWrite(R_FWD, LOW);
  digitalWrite(R_BWD, HIGH);
}