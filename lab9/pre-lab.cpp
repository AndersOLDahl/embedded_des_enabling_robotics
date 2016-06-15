#include <stdlib.h>
#include <stdio.h>

/**
 * Calculate the on period of a PWM signal for controlling a servomotor. The C++
 * function receives the servo position (0 to 180 degrees) and returns the time
 * in micro seconds that PWM signal should be on during each period so that the
 * RC servo moves to the specified servo position.
 *
 * @param position, an integer representing the servo position
 * @return integer, time in micro seconds
 */
int degreeToOnDelay(int position) {
    if (position > 180 || position < 0)
        printf("Position not inclusively between 0 and 180.\n");
        exit(0);

    return position * 10 + 600;

}
