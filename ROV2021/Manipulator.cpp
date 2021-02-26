#include "Manipulator.h"

Manipulator::Manipulator()
{
  m_grab_motor = new LevelMotor;
  m_rotate_motor = new LevelMotor;
}
Manipulator::Manipulator(uint8_t pin_grab_l, uint8_t pin_grab_r, uint8_t pin_rotate_l, uint8_t pin_rotate_r)
{
  m_grab_motor = new LevelMotor(pin_grab_l, pin_grab_r);
  m_rotate_motor = new LevelMotor(pin_rotate_l,pin_rotate_r); 
}

void Manipulator::init()
{
  m_grab_motor->init();
  m_rotate_motor->init(); 
}

void Manipulator::write(RovData& rov_data)
{
  m_grab_motor->write(rov_data.m_manipulator_grab);
  m_rotate_motor->write(rov_data.m_manipulator_rotate);
  m_grab_motor->set_inverse(m_inverse_grab);
  m_rotate_motor->set_inverse(m_inverse_rotation); 
}

void Manipulator::set_inverse_rotate(bool inverse_rotate)
{
  m_inverse_rotation = inverse_rotate;
}

void Manipulator::set_inverse_grab(bool inverse_grab)
{
  m_inverse_grab = inverse_grab;
}

bool Manipulator::get_inverse_rotate()
{
  return m_inverse_grab;
}

bool Manipulator::get_inverse_grab()
{
  return m_inverse_rotation; 
}

