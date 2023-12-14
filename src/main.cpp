#include <Arduino.h>
#include "main.h"
#include "GyverPID.h"

GyverPID regulator(5, 0.03, 0.5, 10);



void setup() {
  Serial.begin(9600);

  regulator.setDirection(NORMAL); 
  regulator.setLimits(-50, 50);
  regulator.setpoint = 0;



}
void loop() {
  unsigned long currentMillis = millis();

  

  leftSensor = ultrasonicSensors[0].dist();
  frontSensor = ultrasonicSensors[1].dist();
  rightSensor = ultrasonicSensors[2].dist();
  backSensor = ultrasonicSensors[3].dist();

  if (leftSensor > 100) {
    leftSensor = 100;
  }
  if (frontSensor > 100) {
    frontSensor = 100;
  }
  if (rightSensor > 100) {
    rightSensor = 100;
  }
  if (backSensor > 100) {
    backSensor = 100;
  }

  
  if(leftSensor <= 15 && rightSensor <= 15) {
    regulator.input = leftSensor - rightSensor;
  }
  if (rightSensor > 17 && leftSensor <= 15) {
    regulator.input = -(9 - leftSensor); 
  } 

  if (leftSensor > 17 && rightSensor <= 15) {
    regulator.input = -( rightSensor - 3); 
  }


  





  
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
  




  

 data = "#" + String(leftSensor) + "," + String(frontSensor) + "," + String(rightSensor) + "," + String(backSensor) + "," + String(resultpidside) + "," + String(moveLeft) + "," + String(moveRight) + "%";

Serial.println(data);

}


  