#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include <stdint.h>
#include "LevelMotor.h"
#include "RovData.h"

class Manipulator
{
public:
  Manipulator();
  Manipulator(uint8_t pin_grab_l, uint8_t pin_grab_r, uint8_t pin_rotate_l, uint8_t pin_rotate_r); 
  void init();
  void write(RovData& rov_data);       
  void set_inverse_rotate(bool inverse_rotate);
  void set_inverse_grab(bool inverse_grab);
  bool get_inverse_rotate();
  bool get_inverse_grab();
private:
  bool m_inverse_grab = false;
  bool m_inverse_rotation = false;
  LevelMotor* m_grab_motor;
  LevelMotor* m_rotate_motor;
};

#endif // !MANIPULATOR_H 
