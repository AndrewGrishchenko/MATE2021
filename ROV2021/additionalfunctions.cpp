#include "additionalfunctions.h"

long map(long x, long in_min, long in_max, long out_min, long out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int constrain(int x, int min, int max)
{
  if (x>max)
  {
    return max; 
  }
  else if (x<min)
  {
    return min;
  }
  else 
  {
    return x;
  }
}
