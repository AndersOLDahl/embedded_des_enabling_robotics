#ifndef _FURNITURE_H_
#define _FURNITURE_H_

#include <string>
using std::string;

class Furniture {
    private:
        /**
         * Three private floating-point numbers indicating the dimensions of
         * the piece of furniture
        */
        float width;
        float height;
        float depth;
        string unique_name; // A private string containing a unique name
    public:
        /**
         * A public constructor that takes the name of the piece of furniture
         * as an argument
         */
        Furniture(string name);

        // Used to read the values of the width, height, and depth
        void ReadDimensions();

        // Print the dimensions and name
        virtual void Print();
};

#endif

