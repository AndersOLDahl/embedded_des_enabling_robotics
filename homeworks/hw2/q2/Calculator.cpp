#include "Calculator.h"

/**
 * Initializes values to default
 */
template <class T>
Calculator<T>::Calculator() {
    value1 = 0;
    value2 = 0;
}

/**
 * Set values
 */
template <class T>
Calculator<T>::Calculator(T value1, T value2) {
    this->value1 = value1;
    this->value2 = value2;
}

/**
 * Returns value1
 */
template <class T>
T Calculator<T>::getValue1() {
    return value1;
}

/**
 * Returns value2
 */
template <class T>
T Calculator<T>::getValue2() {
    return value2;
}

/**
 * Sum of the two templated values
 *
 * @return T, sum of the templated values
 */
template <class T>
T Calculator<T>::getSum() {
    return value1 + value2;
}

/**
 * Logical AND of the two templated values
 *
 * @return an integer, 0 false and 1 true
 */
template <class T>
int Calculator<T>::getLogicalAND() {
    return value1 && value2;
}

/**
 * Greater than of the two templated values
 *
 * @return a boolean, true or false
 */
template <class T>
bool Calculator<T>::isGreater() {
    return value1 > value2;
}
