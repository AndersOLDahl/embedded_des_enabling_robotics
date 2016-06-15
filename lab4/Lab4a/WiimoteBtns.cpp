#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "WiimoteBtns.h"

/**
 * Opens /dev/input/event2 and checks for errors.
 */
WiimoteBtns::WiimoteBtns() {

    // Open Wiimote event file
    fd = open("/dev/input/event2", O_RDONLY);

    if (fd == -1) // Error openining the file descriptor
    {
        std::cerr << "Error: Could not open event file - forgot sudo?\n";
        exit(1);
    }
}

/**
 * Closes the file descriptor
 */
WiimoteBtns::~WiimoteBtns() {
    close(fd);
}

/**
 * Enters an infinite loop where a new event is read from the virtual file.
 * When an event is ready, its associated code and value fields are passed
 * in an invocation to ButtonEvent().
 */
void WiimoteBtns::Listen() {
    while (true)
    {
        // Read a packet of 32 bytes from Wiimote
        char buffer[32];
        read(fd, buffer, 32);

        // Extract code (byte 10) and value (byte 12) from packet
        int code = buffer[10];
        int value = buffer[12];

        this->ButtonEvent(code, value);
    }
}

/**
 * Displays a message on the screen reporting two values.
 *
 * @param code, a number showing the code
 * @param value, a number showing the value
 */
void WiimoteBtns::ButtonEvent(int code, int value) {

    // Print them
    std::cout << "Code = " << code << ", value = " << value << '\n';

}
