#include "Arduino.h"
#include "Communicator.h"
Communicator::Communicator()
{

}
void Communicator::init()
{
  Serial.begin(9600); 
}
void Communicator::read()
{
  if (Serial.available())
  {
    m_speed = 100;
  }
}
int8_t Communicator::retry()
 {
  return m_speed; 
 }
