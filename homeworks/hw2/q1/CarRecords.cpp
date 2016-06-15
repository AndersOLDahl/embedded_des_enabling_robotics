#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <fstream>
using std::ifstream;

/**
 * Class Car representing a car
 */
class Car
{
    private:
        string make;
        string model;
        int year;
        string color;
    public:
        Car(); // Default constructor sets the data fields to default values

         // Sets the class member fields to the values passed
        void setFields(string mk, string md, int yr, string cl);

        string getMake(); // Returns make
        string getModel(); // Returns model
        int getYear(); // Returns year
        string getColor(); // Returns color
};

/**
 * Class CarRecords representing a record of a car
 */
class CarRecords
{
    private:
        int arraysize; // Keep track of number of records
        ifstream infile; // input file stream used to read from a file
        Car *cars; // a pointer car (to a dynamically allocated array of cars)
    public:
        CarRecords(int size); // Reads file records to array
        ~CarRecords(); // Frees memory and closes file handler
        void printCarRecords();
        void sort_cars_by_make(); // Sorts the records by make in asc order
        void sort_cars_by_year(); // Sorts the records by year in desc order
        void print_duplicates(); // Prints out duplicate records
};

/**
 * Print out the car's information
 */
void print_car_helper(Car * car) {
    cout << car->getMake() << ", " <<
        car->getModel() << ", " <<
        car->getYear() << ", " <<
        car->getColor() << endl; // Print out each car
}

/**
 * Default constructor sets the data fields to their default values
 */
Car::Car()
{
    make = "";
    model = "";
    year = 0;
    color = "";

}

/**
 * Sets the class member fields to the values passed
 *
 * @param mk, string representing make
 * @param md, string representing model
 * @param yr, integer representing year
 * @param cl, string representing color
 */
void Car::setFields(string mk, string md, int yr, string cl)
{
    make = mk;
    model = md;
    year = yr;
    color = cl;
}

/**
 * Returns make
 */
string Car::getMake()
{
    return make;
}

/**
 * Returns model
 */
string Car::getModel()
{
    return model;
}

/**
 * Returns year
 */
int Car::getYear()
{
    return year;
}

/**
 * Returns color
 */
string Car::getColor()
{
    return color;
}

/**
 * Constructor sets the value passed to the arraySize member,
 * creates a dynamic array enough to hold arraySize objects of
 * type Car. In addition, the constructor uses the infile file
 * stream and the setFields() method to initialize all the
 * cars array elements with the car records read from the file.
 *
 * @param size, size of dynamic array
 */
CarRecords::CarRecords(int size)
{

    if (arraysize < 10 && arraysize > 0) {
        arraysize = size;
        cars = new Car[arraysize];
    } else {
        arraysize = 10; // Default size to 10
        cars = new Car[arraysize];
    }

    const int MAX_CHARS_PER_LINE = 512;
    const int MAX_TOKENS_PER_LINE = 4;
    const char* const DELIMITER = ", ";

    infile.open ("CarRecords.txt"); // Open file
    if (!infile.good())
        exit(0); // Error - file not found

    int current_car_index = 0; // Keep track of what car we are on

     // Read each line of the file
    while (!infile.eof() && current_car_index < arraysize)
    {
        char buf[MAX_CHARS_PER_LINE];
        infile.getline(buf, MAX_CHARS_PER_LINE); // Place line in buffer

        // array to store memory addresses of the tokens in buf
        const char* token[MAX_TOKENS_PER_LINE] = {}; // Tokens

        // Parse the line
        token[0] = strtok(buf, DELIMITER); // First token
        if (token[0])
        {

            for (int n = 1; n < MAX_TOKENS_PER_LINE; n++)
            {
                token[n] = strtok(0, DELIMITER); // subsequent tokens
                if (!token[n]) break; // no more tokens
            }
        }

        // Set the current car to the values in the corresponding line
        cars[current_car_index].setFields(token[0], token[1],
                atoi(token[2]), token[3]);
        current_car_index++;
    }
}

/**
 * Destructor frees the memory allocated with new, and closes the file
 * handler
 */
CarRecords::~CarRecords()
{
    delete [] cars;
    infile.close();
}

/**
 * Prints out the car records from the array of objects
 */
void CarRecords::printCarRecords()
{
    printf("PRINTING %d Records! \n", arraysize);
    printf("---------------------\n");
    for(int i = 0; i < arraysize; i++)
    {
        print_car_helper(&cars[i]); // Print out the car details
    }
    cout << endl;
}

/**
 * Sorts the records in ascending order based on the make field,
 * using bubble sort
 */
void CarRecords::sort_cars_by_make()
{
  cout << "SORTING RECORDS BY MAKE....." << endl << endl;

  Car swap; // Temp

  // Bubble sort the cars based on make
  for (int i = 0 ; i < ( arraysize - 1 ); i++)
  {
    for (int j = 0 ; j < arraysize - i - 1; j++)
    {
      if (cars[j].getMake().compare(cars[j+1].getMake()) > 0)
      {
        swap       = cars[j];
        cars[j]   = cars[j+1];
        cars[j+1] = swap;
      }
    }
  }
}

/**
 * Sorts the records in descending order based on the year field
 */
void CarRecords::sort_cars_by_year()
{

  cout << "SORTING RECORDS BY YEAR....." << endl << endl;

  Car swap; // Temp

  // Bubble sort the cars based on year
  for (int i = 0 ; i < ( arraysize - 1 ); i++)
  {
    for (int j = 0 ; j < arraysize - i - 1; j++)
    {
      if (cars[j].getYear() > cars[j+1].getYear())
      {
        swap       = cars[j];
        cars[j]   = cars[j+1];
        cars[j+1] = swap;
      }
    }
  }
}

/**
 * Identifies any repeated records, and prints them out when
 * found. Repeated records means that all the fields are the
 * same
 */
void CarRecords::print_duplicates() {
    cout << "CHECKING FOR DUPLICATES..." << endl;

    Car swap; // Temp

    // Finds duplicates using a bubble-sort like implementation
    for (int i = 0 ; i < arraysize - 1; i++)
    {
        for (int j = i + 1 ; j < arraysize; j++)
        {
            if (cars[i].getMake() == cars[j].getMake() &&
                    cars[i].getModel() == cars[j].getModel() &&
                    cars[i].getYear() == cars[j].getYear() &&
                    cars[i].getColor() == cars[j].getColor())
            {
                print_car_helper(&cars[i]); // Print out the car details
                print_car_helper(&cars[j]); // Print out the car details
            }
        }
    }
}

/**
 * Main funciton
 *
 * @return integer, 0 no error, else error
 */
int main() {
    int numRecs;
    cout << "Number or Records to read? " ;
    cin >> numRecs;
    cout << endl;

    CarRecords *cr = new CarRecords(numRecs);
    // Print car records
    cr->printCarRecords();
    // Sort by Year
    cr->sort_cars_by_year();
    // Print car records
    cr->printCarRecords();
    // Sort by Make
    cr->sort_cars_by_make();
    // Print car records
    cr->printCarRecords();
    // Check for Duplicates
    cr->print_duplicates();
    delete cr;
} // end main
