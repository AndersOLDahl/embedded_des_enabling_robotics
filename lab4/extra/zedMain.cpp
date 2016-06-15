#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "ZedBoard.h"
#include "WiimoteAccel.h"

struct timeval t0_x;
struct timeval t0_y;
struct timeval t0_z;

int x_acceleration = 0;
int y_acceleration = 0;
int z_acceleration = 0;

int x_velocity = 0;
int y_velocity = 0;
int z_velocity = 0;

int x_position = 0;
int y_position = 0;
int z_position = 0;

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
 * and handling it accordingly. It prints the acceleration,
 * velocity, position, and time elapsed.
 *
 * @param  code, an integer representing the code.
 * @param acceleration, an integer representing the acceleration.
 * @return an integer representing errors. 0 for no errors.
 */
int WiimoteToLed::AccelerationEvent(int code, int acceleration)
{
    int x_acceleration_new = 0;
    int y_acceleration_new = 0;
    int z_acceleration_new = 0;

    int x_velocity_new = 0;
    int y_velocity_new = 0;
    int z_velocity_new = 0;

    int x_position_new = 0;
    int y_position_new = 0;
    int z_position_new = 0;

    struct timeval t1_x;
    struct timeval t1_y;
    struct timeval t1_z;

    long time = 0;

    sleep(1);

    if(code == 0)
	   return 0;

    // X coordinate
    if (code == 3) {

        gettimeofday(&t1_x, 0);
	    time = ((t1_x.tv_sec-t0_x.tv_sec)*1000000 + t1_x.tv_usec-t0_x.tv_usec) / 1000000;

	    x_acceleration_new = acceleration;
	    x_velocity_new = x_velocity + (acceleration * time);
	    x_position_new = (pow(x_velocity_new, 2) - pow(x_velocity, 2))
		/ (2 * x_acceleration_new);

	    x_acceleration = x_acceleration_new;
	    x_velocity = x_velocity_new;
	    x_position = x_position_new;
	    t0_x = t1_x;

    // Y coordinate
    } else if (code == 4) {

            gettimeofday(&t1_y, 0);
	    time = ((t1_y.tv_sec-t0_y.tv_sec)*1000000 + t1_y.tv_usec-t0_y.tv_usec) / 1000000;

	    y_acceleration_new = acceleration;
	    y_velocity_new = y_velocity + (acceleration * time);
	    y_position_new = (pow(y_velocity_new, 2) - pow(y_velocity, 2))
		/ (2 * y_acceleration_new);

	    y_acceleration = y_acceleration_new;
	    y_velocity = y_velocity_new;
	    y_position = y_position_new;
	    t0_y = t1_y;

    // Z coordinate
    } else if (code == 5) {

            gettimeofday(&t1_z, 0);
	    time = ((t1_z.tv_sec-t0_z.tv_sec)*1000000 + t1_z.tv_usec-t0_z.tv_usec) / 1000000;

	    z_acceleration_new = acceleration;
	    z_velocity_new = z_velocity + (acceleration * time);
	    z_position_new = (pow(z_velocity_new, 2) - pow(z_velocity, 2))
		/ (2 * z_acceleration_new);

	    z_acceleration = z_acceleration_new;
	    z_velocity = z_velocity_new;
	    z_position = z_position_new;
	    t0_z = t1_z;
    }

    printf("Acceleration: (%d, %d, %d)\n", x_acceleration, y_acceleration, z_acceleration);
    printf("Velocity: (%d, %d, %d)\n", x_velocity, y_velocity, z_velocity);
    printf("Position: (%d, %d, %d)\n", x_position, y_position, z_position);
    printf("Time: (%ld)\n", time);

    return 0;
}

int main()
{
    // Instantiate ZedBoard object statically
    ZedBoard zed_board;

     gettimeofday(&t0_x, 0);
     gettimeofday(&t0_y, 0);
     gettimeofday(&t0_z, 0);

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
