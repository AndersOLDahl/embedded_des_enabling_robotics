#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

// A templated class representing a calculator
template <class T>
class Calculator {
    private:
        T value1;
        T value2;
    public:
        Calculator(); // Initializes values to default
        Calculator(T value1, T value2); //set values
        T getValue1(); // Returns value1
        T getValue2(); // Returns value2
        T getSum(); // Uses arithmetic operator ‘+’
        int getLogicalAND(); // Uses logical operator ‘&&’
        bool isGreater(); // Uses Relational operator ‘>’
};

#endif
