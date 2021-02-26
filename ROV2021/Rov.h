#ifndef ROV_H
#define ROV_H

#include "Manipulator.h"
#include "UDPConnection.h"
#include "RotaryCamera.h"
#include "RovData.h"
#include "ThrustersSubsystem.h"

class Rov
{
public:
  Rov();
  void init();
  void run();
  ~Rov();
private:
  RovData m_rov_data;
  Manipulator* m_manipulator;
  UDPConnection* m_udpconnection;
  RotaryCamera* m_rotary_camera;
  ThrustersSubsystem* m_thrusterssubsystem;
};

#endif // !ROV_H
