#include <stdlib.h>
#include <stdio.h>

#include "GPIO.h"

/**
 * Print the menu and get a selection from the user.
 *
 * @return Number of selection.
 */
int PrintMenu()
{
    int sel;

    printf("Main menu:\n\n" );
    printf("1. Move the base\n" );
    printf("2. Move the bicep\n" );
    printf("3. Move the elbow\n" );
    printf("4. Move the wrist\n" );
    printf("5. Move the gripper\n" );
    printf("6. Exit \n" );
    printf("Select an option: " );

    scanf("%d", &sel); // Scan a digit from the user

    return sel; // Return the chosen digit
}

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
    if (position > 160 || position < 20) {
        printf("Position not inclusively between 20 and 160.\n");
        exit(0);
    }

    return position * 10 + 600;

}

/**
 * Run the navigational loop
 *
 * @return Number on exit. 0 for no errors.
 */
int Run()
{
    int sel;
    int angle;

    // While true
    while(true) {

        // Print the menu and get a selection
        sel = PrintMenu();

	printf("Enter an angle between 20 and 160 degrees: ");
	scanf("%d", &angle); // Scan a digit from the user

	// Open device file 13 on Linux file system		
	GPIO gpio_base(13);

	// Open device file 10 on Linux file system		
	GPIO gpio_bicep(10);

	// Open device file 11 on Linux file system		
	GPIO gpio_elbow(11);

	// Open device file 12 on Linux file system		
	GPIO gpio_wrist(12);

	// Open device file 0 on Linux file system		
	GPIO gpio_gripper(0);

        // Next step depends on the selection made
        switch(sel) {

            // User chose 1
            case 1:
                printf("You selected \"Move the base\"\n\n");

		// Generate 400 periods, this will take 20ms * 400 iterations = 8s
		gpio_base.GeneratePWM(20000, degreeToOnDelay(angle), 400);

                break;

            // User chose 2
            case 2:
                printf("You selected \"Move the bicep\"\n\n");

		// Generate PWM signal with 20ms period and 1.5ms on time.
		gpio_bicep.GeneratePWM(20000, degreeToOnDelay(angle), 400);

                break;

            // User chose 3
            case 3:
                printf("You selected \"Move the elbow\"\n\n");

		// Generate PWM signal with 20ms period and 1.5ms on time.
		gpio_elbow.GeneratePWM(20000, degreeToOnDelay(angle), 400);

                break;

            // User chose 4
            case 4:
                printf("You selected \"Move the wrist\"\n\n");

		// Generate 400 periods, this will take 20ms * 400 iterations = 8s
		gpio_wrist.GeneratePWM(20000, degreeToOnDelay(angle), 400);

                break;

            // User chose 5 
            case 5:
                printf("You selected \"Move the gripper\"\n\n");

		// Generate 400 periods, this will take 20ms * 400 iterations = 8s
		gpio_gripper.GeneratePWM(20000, degreeToOnDelay(angle), 400);

                break;


            // User chose 6
            case 6:
                printf("You selected \"Exit\"\n\n");

                // Return here, with no erros, to exit the function.
                // Clean up will be next
                return 0;

            // User chose soomething not on the menu
            default:
                printf("Please enter a valid number from the menu!\n\n");
                break;
        }

    printf("--------------------\n");

    }
}

int main()
{
	Run();
}
