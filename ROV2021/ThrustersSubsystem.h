#ifndef THRUSTERSSUBSYSTEM_H
#define THRUSTERSSUBSYSTEM_H
#include "RovData.h"
#include "Motor.h"

class ThrustersSubsystem
{
public:
  ThrustersSubsystem();
  void init();
  void write(RovData& rov_data);
private:
  void manual_regulator(int8_t power[], RovData& rov_data);
  Motor* m_motors[8];
};

#endif // !THRUSTERSSUBSYSTEM_H
