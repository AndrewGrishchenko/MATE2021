#include <pigpio.h>
#include <iostream>
#include "Rov.h"
#include <stdlib.h>
#include <unistd.h>

using namespace std;

Rov rov;

int main(void)
{	
	gpioInitialise();
	gpioTerminate();
	gpioInitialise();
cout << "iit started" << endl;	
	rov.init();
cout << "iit ended" << endl;
	sleep(10);
cout << "sleep" << endl;
	std::cout << "start" << std::endl;
	while (true)
	{
		rov.run();
	}
	gpioTerminate();
	return 0;
}

