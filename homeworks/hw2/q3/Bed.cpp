#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "Bed.h"

/**
 * A public constructor that takes the unique name of the bed as the first
 * argument, passed directly to the constructor of the parent class, and
 * the string corresponding to the bed size as the second argument. The
 * constructor should print an error message if an invalid size string is
 * passed.
 *
 * @param unique_name, a string representing the name of the bed
 * @param, bs, represents the bed size
 */
Bed::Bed(string unique_name, string bs) : Furniture(unique_name)
{
    if((bs.length() == 4 || bs.length() == 5) &&
        (bs == "Twin" || bs == "Full" || bs == "Queen" || bs == "King")) {
        bed_size = bs;
    } else {
        cout << "ERROR: The bed size is not the right length, or ";
        cout << "it is not a Twin, Full, Queen, or King." << endl;
    }
}

/**
 * A public function Print() that overrides the function with the same name in
 * the parent class. This function prints common furniture information by invoking
 * the parent class function, and continues printing information specific to a bed
 * (the size string).
 */
void Bed::Print()
{
    Furniture::Print();
    cout << "   " << bed_size << " size" << endl;
}
