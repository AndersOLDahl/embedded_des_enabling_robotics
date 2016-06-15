#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/**
* References:
* http://www.geeksforgeeks.org/given-a-linked-
* list-which-is-sorted-how-will-you-insert-in-sorted-way/
*
* http://stackoverflow.com/questions/21388916/
* bubble-sort-singly-linked-list-in-c-with-pointers
*/

typedef struct Car {
    char car_make[50];
    char car_model[50];
    int year;
    char color[50];
    struct Car * next;
} Car;

// Predeclare functions
void print_cars_array(Car * head);
void ordered_insert(Car ** head, Car * new_car);
int insert_sorted_array(Car ** head, int * count);
void sort_cars_by_year(Car ** head);
void print_duplicates(Car * head);
int PrintMenu();
int Run();

/**
 * Insert car into a linked list such that list[first..last] is
 * sorted, given that list[first..last-1] is already sorted
 *
 * @param Car ** head, a reference to the head of the linked list
 */
void ordered_insert(Car ** head, Car * new_car)
{
    Car * current;
    // Special case for the head
    if (*head == NULL || (strncmp((*head)->car_make, new_car->car_make, 50) >= 0))
    {
        new_car->next = *head;
        *head = new_car;
    }
    else
    {
        // Locate the node before the point of insertion
        current = *head;
        while (current->next != NULL &&
            (strncmp(current->next->car_make, new_car->car_make, 50) < 0))
            {
                current = current->next;
            }
            new_car->next = current->next;
            current->next = new_car;
        }
}

/**
 * Reads the 10 records from the file into a sorted singly linked list.
 * The linked list should be sorted based on the car model. Each ne
 * record from file should be inserted into its correct sorted location
 * in the linked list.
 *
 * @param Car ** head, a reference to the head of the linked list
 * @return Number, return 0 for no error
 */
int insert_sorted_array(Car ** head, int * count)
{
    /**
    * Open the file to read car records from.
    */
    FILE * file;
    file = fopen("./CarRecords.txt", "r");
    if (file == NULL) {
        perror("Error opening the file './CarRecords.txt'");
        return -1;
    }

    // Add car records from the file to the list until no more can be added
    // or the limit of 10 is reached.
    while(true) {
        Car * car = (Car *) malloc(sizeof(Car));
        car -> next = NULL;
        if (fscanf(file, "%49[^,], %49[^,], %d, %49[^,\r\n]\r\n", car->car_make,
                car->car_model, &car->year, car->color) == 4 && *count < 10) {
                    ordered_insert(head, car);
                    (*count)++;
                } else {
                    free(car); // Free the car not used and exit the loop
                    break;
                }
    }

    return 0;
}

/**
 * Print the cars in the list
 *
 * @param Car *, a pointer to the head of the list
 */
void print_cars_array(Car * head)
{
    Car * temp = head;
    while(temp != NULL)
    {
        printf("%s %s %d %s \n", temp->car_make, temp->car_model,
                temp->year, temp->color); // Print the data
        temp = temp->next;
    }
}

/**
 * Sort the linked list of cars by year using bubble sort. The sort
 * relies on the pointers being sorted.
 *
 * @param Car ** head, a reference to the head of the linked list
 */
void sort_cars_by_year(Car ** head)
{
    int done = 0; // True if no swaps were made in a pass

    /**
    * Return if head is NULL or the next element is NULL
    */
    if (*head == NULL || (*head)->next == NULL)
        return;

    /**
    * While the sorting is not finished
    */
    while (!done) {
        Car **head_car = head; // Set head reference
        Car *current_car = *head; // Current car, iterator pointer
        Car *next_car = (*head)->next; // Next car, next pointer

        done = 1;

        /**
        * Loop through the linked list
        */
        while (next_car != NULL) {
            if (strcmp(current_car->color, next_car->color) > 0) {
                current_car->next = next_car->next;
                next_car->next = current_car;
                *head_car = next_car;

                done = 0;
            }

            head_car = &current_car->next;
            current_car = next_car;
            next_car = next_car->next;
        }
    }
}

/**
 * Print the duplicates in the linked list of cars
 *
 * @param Car * head, the head of the linked list
 */
void print_duplicates(Car * head)
{
    Car * first = head;

    if (first == NULL) // Return if head is NULL
        return;

    while (first != NULL)
    {
        Car * second = first->next;

        /**
        * Brutce force method.. For each car check if there is another car
        * in the linked list of cars that matches it.
        */
        while (second != NULL)
        {
            /**
            * Compare first node with second node. Compare all the data to see
            * if equality is true.
            */
            if (strncmp(first->car_make, second->car_make, 50) == 0 &&
            strncmp(first->car_model, second->car_model, 50) == 0 &&
            first->year == second->year &&
            strncmp(first->color, second->color, 50) == 0)
            {
                printf("%s %s %d %s \n", first->car_make, first->car_model,
                        first->year, first->color); // Print duplicate
            }

            second = second->next; // Increment the second node
        }

        first = first->next; // Increment the first node
    }
}

/**
 * Print the menu and get a selection from the user.
 *
 * @return Number of selection.
 */
int PrintMenu()
{
    int sel;

    printf("Main menu:\n\n" );
    printf("1. Print the cars list\n" );
    printf("2. Insert the car records into a sorted linked list\n" );
    printf("3. Sort cars by color\n" );
    printf("4. Print duplicates\n" );
    printf("5. Exit \n" );
    printf("Select an option: " );

    scanf("%d", &sel); // Scan a digit from the user

    return sel; // Return the chosen digit
}

/**
 * Run the navigational loop
 *
 * @return Number on exit. 0 for no errors.
 */
int Run()
{
    int sel;
    Car * head = NULL;
    int count = 0;

    // While true
    while(true) {

        // Print the menu and get a selection
        sel = PrintMenu();

        // Next step depends on the selection made
        switch(sel) {

            // User chose 1
            case 1:
                printf("You selected \"Print the cars list\"\n\n");
                print_cars_array(head);
                break;

            // User chose 2
            case 2:
                printf("You selected \"Insert the car records into a sorted linked list\"\n\n");
                insert_sorted_array(&head, &count);
                break;

            // User chose 3
            case 3:
                printf("You selected \"Sort cars by color\"\n\n");
                sort_cars_by_year(&head);
                break;

            // User chose 4
            case 4:
                printf("You selected \"Print duplicates\"\n\n");
                print_duplicates(head);
                break;

            // User chose 5
            case 5:
                printf("You selected \"Exit\"\n\n");

                // Return here, with no erros, to exit the function.
                // Clean up will be next
                return 0;

            // User chose soomething not on the menu
            default:
                printf("Please enter a valid number from the menu!\n\n");
                break;
        }

    printf("--------------------\n");

    }
}

/**
 * Provides two functions that can compute the sum
 * or the difference using bitwise logical operators.
 *
 * @return Number on exit. 0 for no errors.
 */
int main()
{
    Run();
    return 0;
} //end main
