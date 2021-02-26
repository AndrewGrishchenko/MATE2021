#include "RotaryCamera.h"
#include "Timer.h"
#include "additionalfunctions.h"
#include <pigpio.h>

RotaryCamera::RotaryCamera()
{
    m_timer = new Timer;
    defAngle = 90; 
}

RotaryCamera::RotaryCamera(uint8_t pin)
{
    m_driver = pin;  
    m_timer = new Timer;
    defAngle = 90; 
}

void RotaryCamera::init()
{
    gpioSetMode(m_driver, PI_OUTPUT);
    gpioServo(m_driver, map(defAngle, 0, 180, 1000, 2000));
    m_timer->start();
    setRotationTime(30);
}

void RotaryCamera::write(RovData& rov_data)
{
    if (m_timer->elapsed() > m_rotation_time)
    {
        m_angle += rov_data.m_rotary_camera;
        m_angle = constrain(m_angle, 1, 179);
        m_timer->start();
        gpioServo(m_driver, map(constrain(m_angle, 0, 180), 0, 180, 1000, 2000));
    }
}

void RotaryCamera::setRotationTime(uint8_t time)
{
    m_rotation_time = time; 
}
