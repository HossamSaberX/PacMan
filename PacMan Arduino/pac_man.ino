/* ********************* Includes ********************* */
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(13, 12); // RX, TX of the board not the bluetooth

/* ********************* Motor Pins and Constants Section ********************* */

// Motor pins declarations for Motor 1
#define motor1PWM 11
#define motor1Dir1 9
#define motor1Dir2 10

// Motor pins declarations for Motor 2
#define motor2PWM 3
#define motor2Dir1 4
#define motor2Dir2 5
byte motorSpeed = 170; // Initial motor speed
/* ********************* Setup Section ********************* */

void setup() {
  // Setup motor pins
  pinMode(motor1PWM, OUTPUT);
  pinMode(motor1Dir1, OUTPUT);
  pinMode(motor1Dir2, OUTPUT);
  pinMode(motor2PWM, OUTPUT);
  pinMode(motor2Dir1, OUTPUT);
  pinMode(motor2Dir2, OUTPUT);

  // Setup serial communication
  Serial.begin(9600);
  bluetooth.begin(9600);

  // Initialization messages
  Serial.println("Initializing...");
  Serial.println("Use the Serial Monitor or Bluetooth to send commands (F, B, L, R, I, G, H, J, D, S, 0-9) to control the robot!");

}

/* ********************* Motor Control Functions Section ********************* */
void moveForward() {
  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor1Dir2, HIGH);
  analogWrite(motor1PWM, motorSpeed);

  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor2Dir2, HIGH);
  analogWrite(motor2PWM, motorSpeed);
}

void moveBackward() {
  digitalWrite(motor1Dir1, HIGH);
  digitalWrite(motor1Dir2, LOW);
  analogWrite(motor1PWM, motorSpeed);

  digitalWrite(motor2Dir1, HIGH);
  digitalWrite(motor2Dir2, LOW);
  analogWrite(motor2PWM, motorSpeed);
}

void turnLeft() {
  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor1Dir2, HIGH);
  analogWrite(motor1PWM, motorSpeed);

  digitalWrite(motor2Dir1, HIGH);
  digitalWrite(motor2Dir2, LOW);
  analogWrite(motor2PWM, motorSpeed);
}

void turnRight() {
  digitalWrite(motor1Dir1, HIGH);
  digitalWrite(motor1Dir2, LOW);
  analogWrite(motor1PWM, motorSpeed);

  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor2Dir2, HIGH);
  analogWrite(motor2PWM, motorSpeed);
}

void moveForwardRight() {
  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor1Dir2, HIGH);
  analogWrite(motor1PWM, motorSpeed /2); 

  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor2Dir2, HIGH);
  analogWrite(motor2PWM, motorSpeed);
}

void moveForwardLeft() {
  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor1Dir2, HIGH);
  analogWrite(motor1PWM, motorSpeed);

  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor2Dir2, HIGH);
  analogWrite(motor2PWM, motorSpeed /2); 
}

void moveBackwardRight() {
  digitalWrite(motor1Dir1, HIGH);
  digitalWrite(motor1Dir2, LOW);
  analogWrite(motor1PWM, motorSpeed /2); 

  digitalWrite(motor2Dir1, HIGH);
  digitalWrite(motor2Dir2, LOW);
  analogWrite(motor2PWM, motorSpeed);
}
void moveBackwardLeft() {
  digitalWrite(motor1Dir1, HIGH);
  digitalWrite(motor1Dir2, LOW);
  analogWrite(motor1PWM, motorSpeed);

  digitalWrite(motor2Dir1, HIGH);
  digitalWrite(motor2Dir2, LOW);
  analogWrite(motor2PWM, motorSpeed /2); 
}

void stopMotors() {
  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor1Dir2, LOW);
  analogWrite(motor1PWM, 0);

  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor2Dir2, LOW);
  analogWrite(motor2PWM, 0);
}

// Function to set motor speed based on a percentage
void setSpeed(char percentSpeed) {
  // Ensure the speed is within valid range
  if (percentSpeed < 0) {
    percentSpeed = 0;
  } else if (percentSpeed > 100) {
    percentSpeed = 100;
  }

  // Map the percentage speed to PWM range
  motorSpeed = map(percentSpeed, 0, 100, 0, 255);
}

// Function to process an incoming command 
void processCommand(char command) {
  Serial.println(command);
 
    // Execute the corresponding action based on the command
    switch (command) {
      case '0'...'9':
        setSpeed((command - '0') * 10);
        break;
      case 'F':
        moveForward();
        break;
      case 'B':
        moveBackward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'I':
        moveForwardRight();
        break;
      case 'G':
        moveForwardLeft();
        break;
      case 'J':
        moveBackwardRight();
        break;
      case 'H':
        moveBackwardLeft();
        break;
      case 'S':
        stopMotors();
        break;
      default:
        break;
    }}
// All-Time Running loop
void loop() {
  // Check for incoming commands from Serial
  if (Serial.available()) {
    char command = Serial.read();
    processCommand(command);
  }

  // Check for incoming commands from Bluetooth
  if (bluetooth.available()) {
    char command = bluetooth.read();
    processCommand(command);
  }
}