#include <Arduino.h>
// #include "l293d/motor.h"  
#include "distance/distance.h"

// #define MOTOR_A_IN1 3
// #define MOTOR_A_IN2 5

// #define MOTOR_B_IN1 7
// #define MOTOR_B_IN2 9


Distance leftSensor(A2);
Distance frontSensor(A4);
Distance rightSensor(A6);
Distance backSensor(A0);


void setup() {
    Serial.begin(9600);
    


}

String data = "";

String leftSensorData = "0.0";
String frontSensorData = "0.0";
String rightSensorData = "0.0";
String backSensorData = "0.0";

void loop() {

    leftSensorData = String(leftSensor.GetDistance());
    frontSensorData = String(frontSensor.GetDistance());
    rightSensorData = String(rightSensor.GetDistance());
    backSensorData = String(backSensor.GetDistance());

   data = "#" + leftSensorData + "," + frontSensorData + "," + rightSensorData + "," + backSensorData + "%";
    Serial.print(data);

  

}
