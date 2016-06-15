#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "Furniture.h"

/**
 * A public constructor that takes the name of the piece of furniture as an
 * argument
 *
 * @param name, name of the furniture
 */
Furniture::Furniture(string name)
{
    unique_name = name;
}

/**
 * A public function ReadDimentions, used to read the values of the width,
 * height, and depth from the keyboard. The function should show an error
 * message if any of the entered values is less than 0.
 */
void Furniture::ReadDimensions()
{
    cout << "   Enter width: ";
    cin >> width;
    while(width < 0) {
        cout << "ERROR: Please enter a width above 0." << endl;
        cout << "   Enter width: ";
        cin >> width;
    }

    cout << "   Enter height: ";
    cin >> height;
    while(height < 0) {
        cout << "ERROR: Please enter a height above 0." << endl;
        cout << "   Enter height: ";
        cin >> height;
    }

    cout << "   Enter depth: ";
    cin >> depth;
    while(depth < 0) {
        cout << "ERROR: Please enter a depth above 0." << endl;
        cout << "   Enter depth: ";
        cin >> depth;
    }
}

/**
 * A public virtual function Print(), with no arguments and a void return value.
 * This function should print the dimensions and name
 */
void Furniture::Print()
{
    cout << unique_name << ":" << endl;
    cout << "   Width = " << width << ", height = " << height <<
            ", depth = " << depth << endl;
}
