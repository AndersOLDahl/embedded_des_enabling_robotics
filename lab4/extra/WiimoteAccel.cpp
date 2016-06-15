#include "WiimoteAccel.h"
#include <iostream>
#include <fcntl.h>

/**
 * A class constructor opens /dev/input/event0 (instead of /dev/input/event2 as
 * before) and checks for errors.
 */
WiimoteAccel::WiimoteAccel()
{
	fd = open("/dev/input/event0", O_RDONLY);
	if (fd == -1) // Error opening the file descriptor
	{
		std::cerr << "Error: Could not open event file - forgot sudo?\n";
		exit(1);
	}
}

/**
 * A class destructor closes the file.
 */
WiimoteAccel::~WiimoteAccel()
{
	// Close Wiimote event file
	close(fd);
}

/**
 * A public function called Listen() enters an infinite loop where a new
 * acceleration event is read from the virtual file. When found, the associated
 * code and acceleration values are passed to a public function called
 * AccelerationEvent().
 */
void WiimoteAccel::Listen() {
	while (true)
	{
		// Read a packet of 16 bytes from Wiimote
		char buffer[16];
		read(fd, buffer, 16);

		// Extract code (byte 10) and value (byte 12) from packet
		int code = buffer[10];
		short acceleration = * (short *) (buffer + 12);

		this->AccelerationEvent(code, acceleration);

	}
}

/**
 * A public function called AccelerationEvent() takes a code and acceleration
 * as integer arguments, and displays a message on the screen reporting these
 * two values.
 *
 * @param code, a number representing the code
 * @param acceleration, a number representing the acceleration
 */
int WiimoteAccel::AccelerationEvent(int code, int acceleration)
{
	// Print them
	std::cout << "Code = " << code <<
		", acceleration = " << acceleration << '\n';

	return 0;
}
