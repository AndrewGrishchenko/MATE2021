#include "LevelMotor.h"
#include <pigpio.h>

LevelMotor::LevelMotor()
{
}
LevelMotor::LevelMotor(uint8_t pin_l, uint8_t pin_r)
{
    m_pin_l = pin_l;
    m_pin_r = pin_r;
}
void LevelMotor::init()
{
    gpioSetMode(m_pin_l, PI_OUTPUT);
    gpioSetMode(m_pin_r, PI_OUTPUT); 
}
void LevelMotor::write(int8_t power)
{
    m_power=power; 
    if (power > 0)
    {
        gpioWrite(m_pin_l, PI_HIGH);
        gpioWrite(m_pin_r, PI_LOW);
    }
    else if (power < 0)
    {
        gpioWrite(m_pin_l, PI_LOW);
        gpioWrite(m_pin_r, PI_HIGH);
    }
    else if (power == 0)
    {
        gpioWrite(m_pin_l, PI_LOW);
        gpioWrite(m_pin_r, PI_LOW);
    }
}
