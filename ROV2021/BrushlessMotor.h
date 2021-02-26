#ifndef BRUSHLESSMOTOR_H
#define BRUSHLESSMOTOR_H

#include "Motor.h"
#include <stdint.h>

class BrushlessMotor :public Motor {
public:
  BrushlessMotor();
  BrushlessMotor(uint8_t pin);
  void init();
  void write(int8_t power);
private:
  uint8_t m_driver;
};
#endif // !BRUSHLESSMOTOR_H
