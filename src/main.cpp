#include <Arduino.h>
#include "main.h"
#include "GyverPID.h"

GyverPID regulator(5, 0.008, 0.5, 10);

enum class Direction
{
  STOPED,
  FORWARD,
  RIGHTTURN,
  LEFTTURN,
  CHECKAROUND
};
Direction dir = Direction::FORWARD;

enum class TurnAngle
{
  LEFT,
  RIGHT,
  AROUND
};

void turn(TurnAngle angle);

void setup()
{
  Serial.begin(9600);

  regulator.setDirection(NORMAL);
  regulator.setLimits(-50, 50);
  regulator.setpoint = 0;
}
void loop()
{
  unsigned long currentMillis = millis();

  leftSensor = ultrasonicSensors[0].dist();
  frontSensor = ultrasonicSensors[1].dist();
  rightSensor = ultrasonicSensors[2].dist();
  backSensor = ultrasonicSensors[3].dist();
  {
    if (leftSensor > 100)
    {
      leftSensor = 100;
    }
    if (frontSensor > 100)
    {
      frontSensor = 100;
    }
    if (rightSensor > 100)
    {
      rightSensor = 100;
    }
    if (backSensor > 100)
    {
      backSensor = 100;
    }
  }

  // if (frontSensor < MIN_DISTANCE)
  // {
  //   dir = Direction::STOPED;
  // }
  if (frontSensor > MIN_DISTANCE)
  {
    dir = Direction::FORWARD;
  }

  // detecting if there is a left or a right turn
  if (frontSensor < MIN_DISTANCE )
  {
    if (leftSensor - rightSensor > 10)
    {
      // turn right
      turnRight = true;
      hastoTurn = true;
      rightbeforeTurn = frontSensor;
      dir = Direction::RIGHTTURN;
    }
    else
    {
      // turn left
      turnLeft = true;
      hastoTurn = true;
      leftbeforeTurn = frontSensor;
      dir = Direction::LEFTTURN;
    }
  }

  switch (dir)
  {
  case Direction::FORWARD:
    if (leftSensor <= 15 && rightSensor <= 15)
    {
      regulator.input = leftSensor - rightSensor;
    }
    if (rightSensor > 17 && leftSensor <= 15)
    {
      regulator.input = -(9 - leftSensor);
    }

    if (leftSensor > 17 && rightSensor <= 15)
    {
      regulator.input = -(rightSensor - 3);
    }

    resultpidside = regulator.getResultTimer();

    if (frontSensor > MIN_DISTANCE)
    {
      baseSpeed = 150;
    }
    else
    {
      baseSpeed = 0;
    }

    if (resultpidside > 2)
    {

      moveLeft = abs(resultpidside);
      moveRight = 0;
    }

    if (resultpidside < 2)
    {
      moveRight = abs(resultpidside);
      moveLeft = 0;
    }

    motorA.MotorUpdate(baseSpeed + moveLeft * 2, MotorDirection::FORWARD);
    motorB.MotorUpdate(baseSpeed + moveRight * 2, MotorDirection::FORWARD);

    break;

  case Direction::LEFTTURN:
    // store sensor values before turn to use them after turn
    leftbeforeTurn = leftSensor;
    rightbeforeTurn = rightSensor;
    frontbeforeTurn = frontSensor;
    backbeforeTurn = backSensor;

    tunrning = true;
    while (tunrning)
    {
      // read sensor values
      leftSensor = ultrasonicSensors[0].dist();
      frontSensor = ultrasonicSensors[1].dist();
      rightSensor = ultrasonicSensors[2].dist();
      backSensor = ultrasonicSensors[3].dist();

      motorA.MotorUpdate(100, MotorDirection::FORWARD);
      motorB.MotorUpdate(100, MotorDirection::BACKWARD);

      delay(700);
      if (frontSensor > MIN_DISTANCE)
      {
        tunrning = false;
        dir = Direction::FORWARD;
      }
    }

    break;
  case Direction::RIGHTTURN:
    // store sensor values before turn to use them after turn
    leftbeforeTurn = leftSensor;
    rightbeforeTurn = rightSensor;
    frontbeforeTurn = frontSensor;
    backbeforeTurn = backSensor;

    tunrning = true;
    while (tunrning)
    {
      // read sensor values
      leftSensor = ultrasonicSensors[0].dist();
      frontSensor = ultrasonicSensors[1].dist();
      rightSensor = ultrasonicSensors[2].dist();
      backSensor = ultrasonicSensors[3].dist();

      motorA.MotorUpdate(100, MotorDirection::BACKWARD);
      motorB.MotorUpdate(100, MotorDirection::FORWARD);
      delay(700);
      if (frontSensor > MIN_DISTANCE)
      {
        tunrning = false;
        dir = Direction::FORWARD;
      }
    }

    break;

    break;

  default:
    break;
  }

  data = "#" + String(leftSensor) + "," + String(frontSensor) + "," + String(rightSensor) + "," + String(backSensor) + "," + String(resultpidside) + "," + String(moveLeft) + "," + String(moveRight) + "%";

  Serial.println(data);
}

void turn(TurnAngle angle)
{

  if (angle == TurnAngle::LEFT)
  {
  }
  else if (angle == TurnAngle::RIGHT)
  {
  }
  else if (angle == TurnAngle::AROUND)
  {
  }
}