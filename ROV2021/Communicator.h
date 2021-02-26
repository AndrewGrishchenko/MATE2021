#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H
#include "Arduino.h"
class Communicator
{
public:
  Communicator();
  void init();
  void read();
  int8_t retry();
private:
  int8_t m_speed;
};
#endif // !COMMUNICATOR_H
