#include "Rov.h"
#include <iostream>
using namespace std;

Rov::Rov()
{
    //cout << "gpio_c" << endl;
    m_thrusterssubsystem = new ThrustersSubsystem;
    //cout << "thrusters_c" << endl;
    m_udpconnection = new UDPConnection;
    //cout << "udp_c" << endl;    
    m_rotary_camera = new RotaryCamera(4);
    m_manipulator = new Manipulator(7, 8, 11, 25);
    //cout << "manipulator_c" << endl;
}

void Rov::init()
{
    //cout << "init" << std::endl;
    m_rotary_camera->init();
    m_thrusterssubsystem->init();
    //cout << "thrusters_i" << endl;
    m_manipulator->init();
    //cout << "manipulator_i" << endl;
    m_udpconnection->init();
    //cout << "udp_i" << endl;
}

void Rov::run()
{
    m_udpconnection->read(m_rov_data);
    //cout << "udp_r" << endl;
    m_udpconnection->write(m_rov_data);
    //cout << "udp_w" << endl;
    m_thrusterssubsystem->write(m_rov_data);
    //cout << "thrusters_w" << endl;    
    m_rotary_camera->write(m_rov_data);
    m_manipulator->write(m_rov_data);
    //cout << "manipulator_w" << endl;
}

Rov::~Rov()
{
}
