// Import libraries to use
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Reference:
// http://www.anyexample.com/programming/c/qsort__sorting_array_of_strings__integers_and_structs.xml

// An integer comparative function that works with qsort. The arguments need to
// be in the format given for it to work with qsort. Takes in a void * a and a
// void * b which can basically be anything. We will make it less generic later.
int strcmpfunc (const void * a, const void * b)
{
    // Cast the void*'s to be character pointer pointers and then dereference them.
    // This is done in order to avoid issues we were having with the consts.
    // Lastly, it follows how a comparative function that should work with qsort.
    // A negative values means >, 0 is =, and a positive value is <. This is
    // what strcmp returns.
    char const **ia = (const char **)a;
    char const **ib = (const char **)b;
    return strcmp(*ia, *ib);
}

// A main function that runs the entire program. We take in an argc and argv,
// but they are not used in the program. It is standard practice to include
// them.
int main( int argc, char *argv[] )
{
    // Declare the size of the array and initalize an array that can hold 10
    // strings. We need to allocate space for each string individually later.
    int size_of_array = 10;
    char * strings[10];

    // Enter values for the 10 strings using scanf.
    int i;
    for(i = 0; i < size_of_array; i++) {
        // We need to malloc some space for the strings we are entering from
        // command line
        strings[i] = (char *) malloc(50);
        printf("Enter the %d string: ", i+1);

        // Scanf needs to take in a pointer.
        scanf("%s", strings[i]);
    }

    // Sort the values using qsort and our custom cmp function. It needs the
    // sizeof(char *) because we are comparing and sorting strings in this case.
    qsort(strings, size_of_array, sizeof(char *), strcmpfunc);

    // Print the sorted strings
    int n;
    printf("Here are the sorted values: ");
    for( n = 0 ; n < size_of_array; n++ )
    {
        printf("%s ", strings[n]);
    }
    printf("\n");

    // Exit the program and return.
    return 0;
}
