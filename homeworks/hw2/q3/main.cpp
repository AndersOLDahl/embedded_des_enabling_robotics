#include "Table.h"
#include "Bed.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main()
{
    string un, t;

    cout << "Creating table..." << endl;
    cout << "   Enter name: ";
    cin >> un;
    cout << "   Enter wood type (Pine, Oak): ";
    cin >> t;
    Table table = Table(un, t);
    table.ReadDimensions();

    cout << "Creating bed..." << endl;
    cout << "   Enter name: ";
    cin >> un;
    cout << "   Enter size (Twin, Full, Queen, King): ";
    cin >> t;
    Bed bed = Bed(un, t);
    bed.ReadDimensions();

    cout << endl << "Printing objects ..." << endl << endl;
    table.Print();
    bed.Print();
}
