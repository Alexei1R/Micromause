

#pragma once
#include <Arduino.h>

class Distance{
public:
  Distance(int pin);
  float GetDistance(int times = 50);
private:
  float Vr=5.0;
  float k1=16.7647563;
  float k2=-0.85803107;
  int m_Pin;
  float sum=0;
  float sensorVal=0;
  float sensorVolt=0;
  float distance=0;
};


