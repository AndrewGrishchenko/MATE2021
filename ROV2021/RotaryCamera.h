#ifndef ROTARYCAMERA_H
#define ROTARYCAMERA_H

#include <stdint.h>
#include "RovData.h"
#include "Timer.h"

class RotaryCamera 
{
public:
  RotaryCamera();
  RotaryCamera(uint8_t pin); 
  void init(); 
  void write(RovData& rov_data); 
  void setRotationTime(uint8_t time); 
private:
  Timer* m_timer;
  uint8_t m_driver; 
  uint8_t m_angle;
  int8_t m_lastangle = 0;
  int8_t defAngle;
  uint8_t m_rotation_time;
};

#endif // !ROTARYCAMERA_H
