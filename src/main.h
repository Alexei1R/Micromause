#pragma once

#include <Arduino.h>
#include "distance/distance.h"
#include "l293d/motor.h"
#include "pid/pid.h"

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

#define MOTOR_B_IN1 9
#define MOTOR_B_IN2 7

#define MIN_DISTANCE 15 


unsigned long previousMillis = 0;
unsigned long motorUpdateMillis = 0;
const long interval = 10;
const long motorInterval = 100; // Interval for motor update
int sensorIndex = 0;
int motorSpeed = 0;

float leftSensor = 0.0;
float frontSensor = 0.0;
float rightSensor = 0.0;
float backSensor = 0.0;

String data = "";

float setpoint = 0.0;
float measurement;
float control;

int resultpidside;
int  baseSpeed = 0;

int moveLeft = 0;
int moveRight = 0;



SENSOR ultrasonicSensors[4] = {
  SENSOR(TRIG_PIN1, ECHO_PIN1),
  SENSOR(TRIG_PIN2, ECHO_PIN2),
  SENSOR(TRIG_PIN3, ECHO_PIN3),
  SENSOR(TRIG_PIN4, ECHO_PIN4)
};

Motor motorA(MOTOR_A_IN1, MOTOR_A_IN2);
Motor motorB(MOTOR_B_IN1, MOTOR_B_IN2);

