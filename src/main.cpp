#include <Arduino.h>
#include "main.h"
#include "GyverPID.h"

GyverPID regulator(5,0.03, 0.5, 10);


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
    baseSpeed = 150;
  } else {
    baseSpeed = 0;
  }

  
  if( resultpidside > 2){
    
    moveLeft = abs(resultpidside);
    moveRight =0;
  } 
  
  if(resultpidside < 2) {
    moveRight = abs(resultpidside);
    moveLeft = 0;
  }

  motorA.MotorUpdate(baseSpeed +  moveLeft*2, MotorDirection::FORWARD);
  motorB.MotorUpdate(baseSpeed + moveRight*2, MotorDirection::FORWARD);
  
  

  // motorA.MotorUpdate(150 , MotorDirection::FORWARD);
  // motorB.MotorUpdate(150 , MotorDirection::FORWARD);
  
  

 data = "#" + String(leftSensor) + "," + String(frontSensor) + "," + String(rightSensor) + "," + String(backSensor) + "," + String(resultpidside) + "," + String(moveLeft) + "," + String(moveRight) + "%";

Serial.print(data);

}