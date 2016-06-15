#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "Table.h"

/**
 * A public constructor that takes the unique name of the table as the first
 * argument, passed directly to the constructor of the parent class, and the
 * string corresponding to the wood type as the second argument. The constructor
 * should print an error message if an invalid size string is passed.
 *
 * @param unique_name, name of the table
 * @param wt, wood type of the table
 */
Table::Table(string unique_name, string wt) : Furniture(unique_name)
{
    if((wt.length() == 3 || wt.length() == 4) &&
        (wt == "Pine" || wt == "Oak")) { // If equal to length and strings
        wood_type = wt;
    } else
    {
        cout << "ERROR: The wood type is not the right length, or ";
        cout << "it is not an Oak or Pine woodtype." << endl;
    }
}

/**
 * A public function Print() that overrides the function with the same
 * name in the parent class. This function prints common furniture
 * information by invoking the parent class function, and continues
 * printing information specific to a table (the wood type).
 */
void Table::Print()
{
    Furniture::Print();
    cout << "   " << wood_type << " wood" << endl;
}
