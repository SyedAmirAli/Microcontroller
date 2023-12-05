/**
 * @param $connection of the motor with L298N motor driver.
 * Connect the left-top motor to OUT1 and OUT2.
 * Connect the left-bottom motor to OUT3 and OUT4.
 * Connect the right-top motor to OUT1 and OUT2.
 * Connect the right-bottom motor to OUT3 and OUT4.

 * Only For Esp32 Devkit V1
 */

#define BLYNK_TEMPLATE_ID "TMPLSgETUamP"
#define BLYNK_TEMPLATE_NAME "COLLAGE PROJECT"
#define BLYNK_AUTH_TOKEN "Gq2xJ7uj2RbCqHurMycIC_UOpc1YE3by"

#define WIFI_SSID "MICROCONTROLLER"
#define WIFI_PASSWORD "mcu32@amir"

#include <BlynkSimpleEsp32.h>

// use GPIO/D14 ENA pin of the L298N module
const int ENA = 13;
// use GPIO/D33 IN1 pin of the L298N module
const int IN_ONE = 14;
// use GPIO/D35 IN2 pin of the L298N module
const int IN_TWO = 15;
// use GPIO/D26 IN3 pin of the L298N module
const int IN_THREE = 16;
// use GPIO/D27 IN4 pin of the L298N module
const int IN_FOUR = 17;
// use GPIO/D12 - ENB pin of the L298N module
const int ENB = 18;

// initial motor speed
int speed = 130;

void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);

  pinMode(ENA, OUTPUT);  
  pinMode(IN_ONE, OUTPUT);  
  pinMode(IN_TWO, OUTPUT);  
  pinMode(IN_THREE, OUTPUT);  
  pinMode(IN_FOUR, OUTPUT);  
  pinMode(ENB, OUTPUT); 

  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(v0) 
{
  speed = param.asInt();

  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

// Forward button
BLYNK_WRITE(V1) {  
    if (param.asInt() == HIGH) {
        // Move forward
        digitalWrite(IN_ONE, HIGH);
        digitalWrite(IN_TWO, LOW);
        digitalWrite(IN_THREE, HIGH);
        digitalWrite(IN_FOUR, LOW);
    } else {
        // Stop
        stopMotors();
    }
}

// Backward button
BLYNK_WRITE(V2) {  
    if (param.asInt() == HIGH) {
        // Move backward
        digitalWrite(IN_ONE, LOW);
        digitalWrite(IN_TWO, HIGH);
        digitalWrite(IN_THREE, LOW);
        digitalWrite(IN_FOUR, HIGH);
    } else {
        // Stop
        stopMotors();
    }
}

// 360 degrees rotation button
BLYNK_WRITE(V5) {  
    if (param.asInt() == HIGH) {
        // Rotate 360 degrees (Left wheel forward, right wheel backward)
        digitalWrite(IN_ONE, HIGH);
        digitalWrite(IN_TWO, LOW);
        digitalWrite(IN_THREE, LOW);
        digitalWrite(IN_FOUR, HIGH);
    } else {
        // Stop
        stopMotors();
    }
}

// Left turn button
BLYNK_WRITE(V3) {  
    if (param.asInt() == HIGH) {
        // Turn left (Right wheel forward)
        digitalWrite(IN_ONE, HIGH);
        digitalWrite(IN_TWO, LOW);
        digitalWrite(IN_THREE, HIGH);
        digitalWrite(IN_FOUR, LOW);
    } else {
        // Stop
        stopMotors();
    }
}

// Right turn button
BLYNK_WRITE(V4) {  
    if (param.asInt() == HIGH) {
        // Turn right (Left wheel forward)
        digitalWrite(IN_ONE, LOW);
        digitalWrite(IN_TWO, HIGH);
        digitalWrite(IN_THREE, LOW);
        digitalWrite(IN_FOUR, HIGH);
    } else {
        // Stop
        stopMotors();
    }
} 

void stopMotors() {
    // Stop all motors
    digitalWrite(IN_ONE, LOW);
    digitalWrite(IN_TWO, LOW);
    digitalWrite(IN_THREE, LOW);
    digitalWrite(IN_FOUR, LOW);
}
