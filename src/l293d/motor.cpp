#include "motor.h"



Motor::Motor(int pin1, int pin2)
{
    this->pin1 = pin1;
    this->pin2 = pin2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
}

void Motor::MotorUpdate(int speed, MotorDirection direction)
{
    //map speed between 0 and 255
    // speed = map(speed, 0, 100, 0, 255);

    //make shure speed is between 0 and 255
    speed = constrain(speed, 0, 255);
    

    switch (direction)
    {
    case MotorDirection::BACKWARD:
        analogWrite(pin1, speed);
        analogWrite(pin2, LOW);
        break;
    case MotorDirection::FORWARD:
        analogWrite(pin1, LOW);
        analogWrite(pin2, speed);
        break;
    case MotorDirection::STOP:
        analogWrite(pin1, LOW);
        analogWrite(pin2, LOW);
        break;
    default:
        break;
    }
}