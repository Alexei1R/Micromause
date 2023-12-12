#include <Arduino.h>



#ifndef L293D_H
#define L293D_H

enum class MotorDirection{
    FORWARD,
    BACKWARD,
    STOP
};



class Motor{
public:
    Motor(int pin1, int  pin2);


    void MotorUpdate(int speed , MotorDirection direction);

private:
    int pin1;
    int pin2;
    int speed;

};





#endif // L293D_H