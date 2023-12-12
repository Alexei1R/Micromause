#include <Arduino.h>
#include "l293d/motor.h"


#define MOTOR_A_IN1 3
#define MOTOR_A_IN2 5

#define MOTOR_B_IN1 7
#define MOTOR_B_IN2 9


Motor motorA(MOTOR_A_IN1, MOTOR_A_IN2);
Motor motorB(MOTOR_B_IN1, MOTOR_B_IN2);


void setup() {

}

void loop() {



  for(int i = 0;i < 100;i++){
    motorA.MotorUpdate(i, MotorDirection::FORWARD);
    motorB.MotorUpdate(i, MotorDirection::FORWARD);
    delay(50);
  }

}
