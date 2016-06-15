#ifndef _BED_H_
#define _BED_H_

#include <string>
using std::string;

#include "furniture.h"

class Bed: public Furniture {
    private:
        string bed_size; // Specifying the size of the bed
    public:
        Bed(string unique_name, string bt); // Public constructor
        void Print(); // Prints bed information
};

#endif

