#include "BrushlessMotor.h"
#include "pigpio.h"
#include "additionalfunctions.h"

BrushlessMotor::BrushlessMotor()
{
  
}
BrushlessMotor::BrushlessMotor(uint8_t pin)
{
  m_driver = pin;
}

void BrushlessMotor::init()
{
  gpioSetMode(m_driver, PI_OUTPUT);
  gpioServo(m_driver, 1500);
}

void BrushlessMotor::write(int8_t power)
{
  m_power = constrain(power, -100, 100);
  m_power = m_is_inverse ? m_power * -1 : m_power;
 gpioServo(m_driver, map(m_power, -100, 100, 1000, 2000));
}
