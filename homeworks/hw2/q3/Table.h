#ifndef _TABLE_H_
#define _TABLE_H_

#include <string>
using std::string;

#include "furniture.h"

class Table: public Furniture {
    private:
        string wood_type; // A private string indicating the type of wood
    public:
        Table(string unique_name, string bed_size); // A public constructor
        void Print(); // Print table information
};

#endif

