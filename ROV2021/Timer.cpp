#include "Timer.h"
#include <chrono>

Timer::Timer()
{
}

void Timer::start()
{ 
  m_time_start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();;
  m_is_started = true;
}

bool Timer::is_started()
{
  return m_is_started; 
}

void Timer::stop()
{
  m_is_started = false; 
}

long int Timer::elapsed()
{
  if (m_is_started == false)
  {  
    return 0; 
  }
  else 
  {
    long int x = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - m_time_start;
    return x; 
  }
}
