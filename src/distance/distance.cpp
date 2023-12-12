#include "distance.h"

Distance::Distance(int pin)
: m_Pin(pin)
{
    pinMode(m_Pin, INPUT);
}

float Distance::GetDistance(int times)
{
    sum = 0;
    for(int i = 0; i < times; i++)
    {
        sum += float(analogRead(m_Pin));
    }
    sensorVal = sum / times;
    sensorVolt = sensorVal * Vr / 1024;
    distance = pow(sensorVolt * (1 / k1), 1 / k2);
    return distance;
}
