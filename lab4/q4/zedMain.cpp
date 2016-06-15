#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "ZedBoard.h"
#include "WiimoteAccel.h"

// Class definition
class WiimoteToLed : public WiimoteAccel {
        private:
                ZedBoard * zed_p; // Pointer to a ZedBoard
        public:
                WiimoteToLed(ZedBoard * zed);
                int AccelerationEvent(int code, int acceleration);
};

WiimoteToLed::WiimoteToLed(ZedBoard * zed)
{
        zed_p = zed; // Set zedboard
}

/**
 * An acceleration event taking in an acceleration from the Wiimote
 * and handling it accordingly.
 *
 * @param  code, an integer representing the code.
 * @param acceleration, an integer representing the acceleration.
 * @return an integer representing errors. 0 for no errors.
 */
int WiimoteToLed::AccelerationEvent(int code, int acceleration)
{
    if (code != 3)
        return 0;

    if (acceleration < -100)
        acceleration = -100;

    if (acceleration > 100)
        acceleration = 100;

    // Print them
    std::cout << "Code = " << code <<
    	", acceleration = " << acceleration << '\n';

    // How many LEDs to light up.
    acceleration = (double) abs(acceleration) / 100 * 8;

    // Sets the LEDs based on the acceleration.
    int i;
    for(i = 0; i < 8; i++) {
        if(i < acceleration) {
            zed_p -> Set1Led(i, 1);
        } else {
            zed_p -> Set1Led(i, 0);
        }
    }

    return 0;
}

int main()
{
    // Instantiate ZedBoard object statically
    ZedBoard zed_board;
    // Instantiate WiimoteToLed object statically, passing a pointer to the
    // recently created ZedBoard object.
    WiimoteToLed wiimote_to_led(&zed_board);
    // Enter infinite loop listening to events. The overridden function
    // WiimoteToLed::AccelerationEvent() will be invoked when the user moves
    // the Wiimote.
    wiimote_to_led.Listen();
    // Unreachable code, previous function has an infinite loop
    return 0;
}
