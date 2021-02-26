#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

class Motor {
public:
  virtual void init() = 0;
  virtual void write(int8_t power) = 0;
  void set_inverse(bool inverse);
  bool get_inverse();
  int8_t get_power();
protected:
  int8_t m_power;
  bool m_is_inverse = false;
};
#endif // !MOTOR_H
