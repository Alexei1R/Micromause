#include <Arduino.h>
#include "distance/distance.h"
#include "l293d/motor.h"

#define TRIG_PIN1 15
#define ECHO_PIN1 17
#define TRIG_PIN2 6
#define ECHO_PIN2 8
#define TRIG_PIN3 10
#define ECHO_PIN3 12
#define TRIG_PIN4 14
#define ECHO_PIN4 16


#define MOTOR_A_IN1 3
#define MOTOR_A_IN2 5

#define MOTOR_B_IN1 7
#define MOTOR_B_IN2 9

#define MIN_DISTANCE 15 

unsigned long previousMillis = 0;
unsigned long motorUpdateMillis = 0;
const long interval = 10;
const long motorInterval = 100; // Interval for motor update
int sensorIndex = 0;
int motorSpeed = 0;

float leftMotor = 0.0;
float frontMotor = 0.0;
float rightMotor = 0.0;
float backMotor = 0.0;

String data = "";

SENSOR ultrasonicSensors[4] = {
  SENSOR(TRIG_PIN1, ECHO_PIN1),
  SENSOR(TRIG_PIN2, ECHO_PIN2),
  SENSOR(TRIG_PIN3, ECHO_PIN3),
  SENSOR(TRIG_PIN4, ECHO_PIN4)
};

Motor motorA(MOTOR_A_IN1, MOTOR_A_IN2);
Motor motorB(MOTOR_B_IN1, MOTOR_B_IN2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  // Sensor update logic
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    float distance = ultrasonicSensors[sensorIndex].dist();
    switch(sensorIndex) {
      case 0: leftMotor = distance; break;
      case 1: frontMotor = distance; break;
      case 2: rightMotor = distance; break;
      case 3: backMotor = distance; break;
    }
    sensorIndex = (sensorIndex + 1) % 4;
    data = "#" + String(leftMotor) + "," + String(frontMotor) + "," + String(rightMotor) + "," + String(backMotor) + "%";
    Serial.print(data);
  }

  
  // if (currentMillis - motorUpdateMillis >= motorInterval) {
  //   motorUpdateMillis = currentMillis;
  //   if (frontMotor > MIN_DISTANCE) {
  //     motorA.MotorUpdate(100, MotorDirection::FORWARD); 
  //     motorB.MotorUpdate(100, MotorDirection::FORWARD);
  //   }
  //   else if (backMotor > MIN_DISTANCE) {
  //     motorA.MotorUpdate(100, MotorDirection::BACKWARD);
  //     motorB.MotorUpdate(100, MotorDirection::BACKWARD);
  //   }
  //   else {
  //     motorA.MotorUpdate(0, MotorDirection::FORWARD); 
  //     motorB.MotorUpdate(0, MotorDirection::FORWARD);
  //   }
  // }




}
