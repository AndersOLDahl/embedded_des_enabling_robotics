#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include "GPIO.h"

GPIO::GPIO(int number)
{
	// GPIO device files will follow the format
	// /sys/class/gpio/gpio<NR>/value
	// <NR> has to be replaced with the actual device number passed as an
	// argument to the class constructor.
	char device_name[128];
	sprintf(device_name, "/sys/class/gpio/gpio%d/value", number);

	// Open special device file and store file descriptor in class member.
	fd = open(device_name, O_WRONLY);
	if (fd < 0)
	{
		std::cerr << "Cannot open " << device_name <<
			" - forgot sudo? \n";
		exit(1);
	}
}

GPIO::~GPIO()
{
	// Close open file descriptor
	close(fd);
}

void GPIO::GenerateVariablePWM(int period, int first_pulse, int last_pulse, int num_periods)
{

	for (int i = 0; i < 50; i++) {
		write(fd, "1", 1);
		usleep(first_pulse);
		write(fd, "0", 1);
		usleep(period - first_pulse);
	}

	num_periods -= 100;
	int pulse = first_pulse;
	int difference = abs(first_pulse - last_pulse) / num_periods;


	for (int i = 0; i < num_periods; i++) {
		write(fd, "1", 1);
		usleep(pulse);
		write(fd, "0", 1);
		usleep(period - pulse);
		if (first_pulse < last_pulse) 
			pulse += difference;
		else
			pulse -= difference;
	}


	for (int i = 0; i < 50; i++) {
		write(fd, "1", 1);
		usleep(last_pulse);
		write(fd, "0", 1);
		usleep(period - last_pulse);
	}
}
