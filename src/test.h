#include <Arduino.h>
#include "main.h"
#include "GyverPID.h"

GyverPID regulator(1 ,0.01, 0.05, 10);


void setup() {
  Serial.begin(9600);

  regulator.setDirection(NORMAL); 
  regulator.setLimits(-50, 50);
  regulator.setpoint = 0;



}
void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    float distance = ultrasonicSensors[sensorIndex].dist();
    if (sensorIndex == 0 || sensorIndex == 2) {
      if (sensorIndex == 0) {
        leftSensor = distance;
      } else {
        rightSensor = distance;
      }

      sensorIndex++;
    } else {
      if (sensorIndex == 1) {
        frontSensor = distance;
      } else {
        backSensor = distance;
      }

      sensorIndex = (sensorIndex + 1) % 4;
    }
  }


  regulator.input  = leftSensor - rightSensor;
  resultpidside = regulator.getResultTimer();

  if (frontSensor > MIN_DISTANCE) {
    baseSpeed = 200;
  } else {
    baseSpeed = 0;
  }

  if( resultpidside < 0){
    moveLeft = abs(resultpidside);
  } else {
    moveRight = abs(resultpidside);
  }

  motorA.MotorUpdate(baseSpeed + moveLeft , MotorDirection::FORWARD);
  motorB.MotorUpdate(baseSpeed + moveRight, MotorDirection::FORWARD);
  
  
  
  

 data = "#" + String(leftSensor) + "," + String(frontSensor) + "," + String(rightSensor) + "," + String(backSensor) + "," + String(resultpidside) + "%";

Serial.print(data);
delay(10);

}