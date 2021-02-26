#ifndef LEVELMOTOR_H
#define LEVELMOTOR_H

#include <stdint.h>
#include "Motor.h"

class LevelMotor : public Motor
{
public:
  LevelMotor();
  LevelMotor(uint8_t pin_l, uint8_t pin_r); 
  void init(); 
  void write(int8_t power); 
private:
  uint8_t m_pin_l;
  uint8_t m_pin_r;
};

#endif // !LEVELMOTOR_H
