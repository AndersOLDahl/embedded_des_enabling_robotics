#include <iostream>
using std::cout;
using std::endl;

#include "Calculator.h"
#include "Calculator.cpp"

// A class representing the arithmetic
class Arithmetic {
    private:
        int intData;
        float floatData;
        double doubleData;

        /** A template function local to this class. The function
        * can be called with different types of objects
        */
        template <class T2>
        void printOperations(T2 obj);
    public:
        Arithmetic(); // A constructor initializes data members to zero
        Arithmetic(int i, float f, double d); // Sets data members to values passed
        void intOperations(Arithmetic obj); // Tests template class on ints
        void floatOperations(Arithmetic obj); // Tests template class on floats
        void doubleOperations(Arithmetic obj); // Tests template class on doubles
};

/**
 * A constructor initializes data members to zero
 */
Arithmetic::Arithmetic() {
    intData = 0;
    floatData = 0;
    doubleData = 0;
}

/**
 * Another constructor sets data members to values
 * passed
 *
 * @param i, represent the integer
 * @param f, represents the float
 * @param d, represents the double
 */
Arithmetic::Arithmetic(int i, float f, double d) {
    intData = i;
    floatData = f;
    doubleData = d;
}

/**
 * A template function local to this class. The function can be called
 * with different types of objects, and it prints out the values and
 * calls getSum(), getLogicalAND(), and isGreater() functions from the
 * template class to test the 3 different types of operations, and print
 * the results from those operations as seen in the sample output below.
 *
 * @param T2, Calculator template object
 */
template <class T2>
void Arithmetic::printOperations(T2 obj) {
    cout << obj.getValue1() << " + " << obj.getValue2()
            << " = " << obj.getSum() << endl;
    cout << obj.getValue1() << " && " << obj.getValue2()
            << " = " << obj.getLogicalAND() << endl;
    cout << obj.getValue1() << " > " << obj.getValue2()
            << " = " << (obj.isGreater() ? "true" : "false") << endl;
}

/**
 * Creates an object of type int from the template class while setting
 * the int values for the two objects, and calls printOperations(T2 obj)
 * function to test the 3 different types of operations
 *
 * @param obj, an Arithmetic object
 */
void Arithmetic::intOperations(Arithmetic obj) {
    Calculator<int> calc = Calculator<int>(this->intData, obj.intData);
    this->printOperations(calc);
}

/**
 * Creates an object of type float from the template class while setting
 * the float values for the two objects, and calls printOperations(T2 obj)
 * function to test the 3 different types of operations
 *
 * @param obj, an Arithmetic object
 */
void Arithmetic::floatOperations(Arithmetic obj) {
    Calculator<float> calc = Calculator<float>(this->floatData, obj.floatData);
    this->printOperations(calc);
}

/**
 * Creates an object of type double from the template class while setting
 * the double values for the two objects, and calls printOperations(T2 obj)
 * function to test the 3 different types of operations
 *
 * @param obj, an Arithmetic object
 */
void Arithmetic::doubleOperations(Arithmetic obj) {
    Calculator<double> calc = Calculator<double>(this->doubleData, obj.doubleData);
    this->printOperations(calc);
}

/**
 * The main function
 */
int main()
{
    // Create 1st object
    int int1 = 4;
    float f1 = 10.4;
    double d1 = 20.1;
    Arithmetic object1(int1, f1, d1);
    // Create 2nd object
    int int2 = 7;
    float f2 = 0.0;
    double d2 = 3.5;
    Arithmetic object2(int2, f2, d2);
    // Check operation on integer data type
    cout << "Printing INTEGER operations..." << endl;
    object1.intOperations(object2);
    // Check operation on float data type
    cout << "\nPrinting FLOAT operations..." << endl;
    object1.floatOperations(object2);
    // Check operation on double data type
    cout << "\nPrinting DOUBLE operations..." << endl;
    object1.doubleOperations(object2);
} // end main
