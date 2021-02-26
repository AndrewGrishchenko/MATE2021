#include "ThrustersSubsystem.h"
#include "additionalfunctions.h"
#include "BrushlessMotor.h"
#include  <pigpio.h>
#include <iostream>

ThrustersSubsystem::ThrustersSubsystem()
{
  m_motors[0] = new BrushlessMotor(5);
  m_motors[1] = new BrushlessMotor(6);
  m_motors[2] = new BrushlessMotor(12);
  m_motors[3] = new BrushlessMotor(13);
  m_motors[4] = new BrushlessMotor(16);
  m_motors[5] = new BrushlessMotor(19);
  m_motors[6] = new BrushlessMotor(20);
  m_motors[7] = new BrushlessMotor(26);

  m_motors[0]->set_inverse(true);
  m_motors[1]->set_inverse(true);
  m_motors[2]->set_inverse(true);
  m_motors[3]->set_inverse(true);
  m_motors[4]->set_inverse(true);
  m_motors[5]->set_inverse(true);
  m_motors[6]->set_inverse(true);
  m_motors[7]->set_inverse(true);
}

void ThrustersSubsystem::init()
{
  for(int i = 0; i<8; i++)
  {
    m_motors[i]->init();
  }
  //gpioDelay(10000000);
}

void ThrustersSubsystem::manual_regulator(int8_t power[], RovData& rov_data)
{  
   power[0] = constrain(rov_data.m_axis_y + rov_data.m_axis_x + rov_data.m_axis_w, -100, 100);
   power[1] = constrain(rov_data.m_axis_y - rov_data.m_axis_x - rov_data.m_axis_w, -100, 100);
   power[2] = constrain(rov_data.m_axis_y - rov_data.m_axis_x + rov_data.m_axis_w, -100, 100);
   power[3] = constrain(rov_data.m_axis_y + rov_data.m_axis_x - rov_data.m_axis_w, -100, 100); 

   power[4] = constrain(rov_data.m_axis_z, -100, 100);
   power[5] = constrain(rov_data.m_axis_z, -100, 100);
   power[6] = constrain(rov_data.m_axis_z, -100, 100);
   power[7] = constrain(rov_data.m_axis_z, -100, 100);
}
void ThrustersSubsystem::write(RovData& rov_data)
{
  int8_t power[8] = {0};    
  manual_regulator(power,rov_data); 
  for (int d=0; d<8; d++)
 {
	//std::cout << d << " " << (int)power[d] << std::endl;
   m_motors[d]->write(power[d]);     
 }
}
