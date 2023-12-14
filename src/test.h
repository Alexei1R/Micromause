#include <Arduino.h>
#include "main.h"
#include "GyverPID.h"

GyverPID regulator(5, 0.03, 0.5, 10);

bool turnLeft = false;
bool turnRight = false;
bool turnAround = false;
bool hastoTurn = false;

int newLeft = 0;
int newRight = 0;
int newFront = 0;
int newBack = 0;

float leftbeforeTurn = 0;
float rightbeforeTurn = 0;
float frontbeforeTurn = 0;
float backbeforeTurn = 0;

enum class TurnAngle {
  LEFT,
  RIGHT,
  AROUND
};

void turn(TurnAngle angle);


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

  if (leftSensor > 25 || rightSensor > 25) {
    if (leftSensor < rightSensor) {
      regulator.input = leftSensor - 10;
    } else {
      regulator.input = rightSensor - 10;
    }
  } else {
    regulator.input = leftSensor - rightSensor;
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

  if(hastoTurn == false){
    motorA.MotorUpdate(baseSpeed +  moveLeft*2, MotorDirection::FORWARD);
    motorB.MotorUpdate(baseSpeed + moveRight*2, MotorDirection::FORWARD);
  }
  

  if(frontSensor < 13 && !hastoTurn){
    if(leftSensor - rightSensor > 10){
      // turn right 
      turnRight = true;
      hastoTurn = true;
      rightbeforeTurn = frontSensor;

    }
    if(rightSensor - leftSensor > 10){
      // turn left 
      turnLeft = true;
      hastoTurn = true;
      leftbeforeTurn = frontSensor;
    }
    if(backSensor - frontSensor > 10){
      // turn around 
      turnAround = true;
      hastoTurn = true;
      backbeforeTurn = frontSensor;
    }
    
  

  }

  if(turnLeft){
    turn(TurnAngle::LEFT);
  }
  if(turnRight){
    turn(TurnAngle::RIGHT);
  }
  if(turnAround){
    turn(TurnAngle::AROUND);
  }
  



  

 data = "#" + String(leftSensor) + "," + String(frontSensor) + "," + String(rightSensor) + "," + String(backSensor) + "," + String(resultpidside) + "," + String(moveLeft) + "," + String(moveRight) + "%";

Serial.print(data);

}



void turn(TurnAngle angle){

  


  // //turn until the front sensor dont show maximum distance  and  turn in distance of maximum distance of the left or right sensor
  if(angle == TurnAngle::LEFT){
    bool val  = false;//= frontSensor < 60;
     if(frontSensor < 60) {
        val = true;
      } else {
        val = false;  
     }

    if (frontSensor < rightbeforeTurn - 10 || frontSensor < 60 && leftSensor > rightSensor) {
      motorA.MotorUpdate(100, MotorDirection::BACKWARD);
      motorB.MotorUpdate(100, MotorDirection::FORWARD);
    } else {
      motorA.MotorUpdate(0, MotorDirection::FORWARD);
      motorB.MotorUpdate(0, MotorDirection::BACKWARD);
      hastoTurn = false;
      turnLeft = false;
    }
  }

  if(angle == TurnAngle::RIGHT){
    if (frontSensor < leftbeforeTurn || frontSensor < 60 && rightSensor > leftSensor) {
      motorA.MotorUpdate(100, MotorDirection::FORWARD);
      motorB.MotorUpdate(100, MotorDirection::BACKWARD);
    } else {
      motorA.MotorUpdate(0, MotorDirection::BACKWARD);
      motorB.MotorUpdate(0, MotorDirection::FORWARD);
      hastoTurn = false;
      turnRight = false;
    }
  }

  // if(angle == TurnAngle::AROUND){
  //   // if  back is bigher than front and diference is minimum 10 cm turn around 
  //   if (frontSensor < 45 && backSensor > frontSensor && backSensor - frontSensor > 10) {
  //     motorA.MotorUpdate(100, MotorDirection::BACKWARD);
  //     motorB.MotorUpdate(100, MotorDirection::FORWARD);
  //   } else {
  //     motorA.MotorUpdate(0, MotorDirection::BACKWARD);
  //     motorB.MotorUpdate(0, MotorDirection::FORWARD);
  //     hastoTurn = false;
  //     turnAround = false;
  //   }
  }