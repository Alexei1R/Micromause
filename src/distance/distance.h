#pragma once
#include <Arduino.h>

#define dist_of_trig 85  // distance of trig
#define resp_time 400    // sensor response time (return true not less than 400 ms)

//----------------------------------------------------- Class -----------------------------------------------------
class SENSOR {
  //-------------------------------- Methodes --------------------------------
public:
  SENSOR(int out, int echo);  // initialisation class SENSOR (trig pin , echo pin)
  float dist();// const;         // return curent distance of element 0

  bool check();
  //-------------------------------- Methodes --------------------------------
  //------------------------------- Parameters -------------------------------
private:
  int _out;   // out pin
  int _echo;  // echo pin list

  uint32_t _tmr;
  bool _flag;
  //------------------------------- Parameters -------------------------------
};
//----------------------------------------------------- Class -----------------------------------------------------

//--------------------------------------------------- Methodes ----------------------------------------------------
SENSOR::SENSOR(int out, int echo) {
  _out = out;
  _echo = echo;
  pinMode(_out, OUTPUT);
  pinMode(_echo, INPUT);
}

bool SENSOR::check() {
  bool btnState;
  if (dist() < dist_of_trig) {
  // if (!digitalRead(_echo)) {
    btnState = false;
    // Serial.println("         false ");
  } else {
    btnState = true;
    // Serial.println("true ");
  }
  if (!btnState && !_flag && millis() - _tmr >= resp_time) {
    _flag = true;
    _tmr = millis();
    return true;
  }
  if (btnState && _flag) {
    _flag = false;
    _tmr = millis();
  }
  return false;
}

//---------------------------
float SENSOR::dist() {//const {
  digitalWrite(_out, LOW);
  delayMicroseconds(2);
  digitalWrite(_out, HIGH);
  delayMicroseconds(10);
  digitalWrite(_out, LOW);
  noInterrupts();
  float d = pulseIn(_echo, HIGH, 23529.4);  // max sensor dist ~4m
  interrupts();
  //  delay(1);
  // Serial.println(d / 58.8235);
  return d / 58.8235;
}
//--------------------------------------------------- Methodes ----------------------------------------------------




// #pragma once
// #include <Arduino.h>

// class Distance{
// public:
//   Distance(int pin);
//   float GetDistance(int times = 50);
// private:
//   float Vr=5.0;
//   float k1=16.7647563;
//   float k2=-0.85803107;
//   int m_Pin;
//   float sum=0;
//   float sensorVal=0;
//   float sensorVolt=0;
//   float distance=0;
// };


