// Import libraries to use
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Reference:
// http://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm

// An integer comparative function that works with qsort. The arguments need to
// be in the format given for it to work with qsort. Takes in a void * a and a
// void * b which can basically be anything. We will make it less generic later.
int cmpfunc (const void * a, const void * b)
{
    // Cast the void*'s to be integer pointers and then dereference them.
    // Lastly, it follows how a comparative function should work with qsort.
    // A negative values means >, 0 is =, and a positive value is <.
    return ( *(int*)a - *(int*)b );
}

// A main function that runs the entire program. We take in an argc and argv,
// but they are not used in the program. It is standard practice to include
// them.
int main( int argc, char *argv[] )
{
    // Declare the size of the array and initalize an array that can hold 10
    // integers.
    int size_of_array = 10;
    int values[10];

    // Enter values for the 10 integers using scanf.
    int i;
    for(i = 0; i < size_of_array; i++) {
        printf("Enter the %d integer: ", i+1);

        // Scanf needs to take in a pointer.
        scanf("%d", &values[i]);
    }

    // Sort the values using qsort and our custom cmp function. It needs the
    // sizeof(int) because we are comparing and sorting integers in this case.
    qsort(values, size_of_array, sizeof(int), cmpfunc);

    // Print the sorted values
    int n;
    printf("Here are the sorted values: ");
    for( n = 0 ; n < size_of_array; n++ )
    {
        printf("%d ", values[n]);
    }
    printf("\n");

    // Exit the program and return.
    return 0;
}
