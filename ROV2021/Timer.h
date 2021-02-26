#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
  Timer();
  void start(); 
  bool is_started(); 
  void stop(); 
  long int elapsed(); 
private:
  long int m_time_start = 0;
  bool m_is_started = false;
};

#endif // !TIMER_H 
