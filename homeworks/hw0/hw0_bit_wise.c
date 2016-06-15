#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/** Reference used:
http://www.pixelstech.net/article/1344149505-Implementation
-of-%2B---*-with-bitwise-operator
*/

// Predeclare functions
int negate(int a);
int add(int a, int b);
int sub(int a, int b);
void printBinary(int x);
int add_prompt();
int sub_prompt();
int PrintMenu();
int Run();

/**
 * Negate the integer. This is equivalent to making
 * a positive value negative and vice versa.
 *
 * @return Answer of negation
 */
int negate(int a)
{
    return add(~a, 1);
}

/**
 * Adds two integers recursively
 *
 * @return Number on exit. 0 for no errors.
 */
int add(int a, int b)
{
    if(b == 0)
        return a;

    /**
     * XOR is the sum of two integers
     * AND is the carry of two integers
     * Recursively loops until no carry is present
     */
    return add( a ^b, (a & b) << 1);
}

/**
 * Subtracts two integers: a-b
 * using bitwise logical operators
 *
 * @return Answer after subtraction
 */
int sub(int a, int b)
{
    /**
     * Add the negation of b
     */
    return add(a, negate(b));
}

/**
 * Print the binary value of the equivalent
 * integer.
 */
void printBinary(int x)
{
    printf("Binary Representation: \n");
    int c, k;

    /**
     * Loop through each bit of the integer
     */
    for (c = sizeof(int) * 8 - 1; c >= 0; c--)
    {
        k = x >> c;

        if (k & 1)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

/**
 * Prompts the user to add two positive integers
 *
 * @return Number on exit. 0 for no errors.
 */
int add_prompt()
{

    int num1;
    int num2;

    printf("Please enter two positive integers. \n");
    printf("Enter the first number: ");
    scanf("%d", &num1); // Scan an int from the user
    printf("Enter the second number: "); // Scan an int from the user
    scanf("%d", &num2);

    int ans = add(num1, num2); // Calculate the addition

    /** Print the answer and return
     */
    printf("Answer: %d\n", ans);
    printBinary(ans);
    return 0;
}

/**
 * Prompts the user to subtract two
 * positive integers
 *
 * @return Number on exit. 0 for no errors.
 */
int sub_prompt()
{

    unsigned int num1;
    unsigned int num2;

    printf("Please enter two positive integers. \n");
    printf("Enter the first number: ");
    scanf("%d", &num1); // Scan an int from the user
    printf("Enter the second number: "); // Scan an int from the user
    scanf("%d", &num2);

    int ans = sub(num1, num2); // Calculate the subtraction

    /** Print the answer and return
     */
    printf("Answer: %d\n", ans);
    printBinary(ans);
    return 0;
}

/**
 * Print the menu and get a selection from the user.
 *
 * @return Number of selection.
 */
int PrintMenu()
{
    int sel;

    printf("Main menu:\n\n" );
    printf("1. Add two positive integers\n" );
    printf("2. Subtract two positive integers\n" );
    printf("3. Exit\n\n" );
    printf("Select an option: " );

    // Scan a digit from the user
    scanf("%d", &sel);

    // Return the chosen digit
    return sel;
}

/**
 * Run the navigational loop
 *
 * @return Number on exit. 0 for no errors.
 */
int Run()
{
    int sel;

    // While true
    while(true) {

        // Print the menu and get a selection
        sel = PrintMenu();

        // Next step depends on the selection made
        switch(sel) {

            // User chose 1
            case 1:
                add_prompt();
                break;

            // User chose 2
            case 2:
                sub_prompt();
                break;

            // User chose 3
            case 3:
                printf("You selected \"Exit\"\n");

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

/**
 * Provides two functions that can compute the sum
 * or the difference using bitwise logical operators.
 *
 * @return Number on exit. 0 for no errors.
 */
int main()
{

    Run();

} //end main
