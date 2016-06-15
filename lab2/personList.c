#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Linked List Management Code
struct Person
{
    // Unique identifier for the person
    int id;
    // Information about person
    char name[20];
    int age;
    // Pointer to next person in list
    struct Person *next;
};
struct List
{
    // First person in the list. A value equal to NULL indicates that the
    // list is empty.
    struct Person *head;
    // Current person in the list. A value equal to NULL indicates a
    // past-the-end position.
    struct Person *current;
    // Pointer to the element appearing before 'current'. It can be NULL if
    // 'current' is NULL, or if 'current' is the first element in the list.
    struct Person *previous;
    // Number of persons in the list
    int count;
};

// Predeclare functions
void sortByName(struct List * list, int * last_unique_id);
void sortByAge(struct List * list, int * last_unique_id);

// Give an initial value to all the fields in the list.
void ListInitialize(struct List *list)
{
    list->head = NULL;
    list->current = NULL;
    list->previous = NULL;
    list->count = 0;
}
// Move the current position in the list one element forward. If last element
// is exceeded, the current position is set to a special past-the-end value.
void ListNext(struct List *list)
{
    if (list->current)
    {
        list->previous = list->current;
        list->current = list->current->next;
    }
}
// Move the current position to the first element in the list.
void ListHead(struct List *list)
{
    list->previous = NULL;
    list->current = list->head;
}
// Get the element at the current position, or NULL if the current position is
// past-the-end.
struct Person *ListGet(struct List *list)
{
    return list->current;
}
// Set the current position to the person with the given id. If no person
// exists with that id, the current position is set to past-the-end.
void ListFind(struct List *list, int id)
{
    ListHead(list);
    while (list->current && list->current->id != id)
        ListNext(list);
}
// Insert a person before the element at the current position in the list. If
// the current position is past-the-end, the person is inserted at the end of
// the list. The new person is made the new current element in the list.
void ListInsert(struct List *list, struct Person *person)
{
    // Set 'next' pointer of current element
    person->next = list->current;
    // Set 'next' pointer of previous element. Treat the special case where
    // the current element was the head of the list.
    if (list->current == list->head)
        list->head = person;
    else
        list->previous->next = person;
    // Set the current element to the new person
    list->current = person;
}
// Remove the current element in the list. The new current element will be the
// element that appeared right after the removed element.
void ListRemove(struct List *list)
{
    // Ignore if current element is past-the-end
    if (!list->current)
        return;
    // Remove element. Consider special case where the current element is
    // in the head of the list.
    if (list->current == list->head)
        list->head = list->current->next;
    else
        list->previous->next = list->current->next;
    // Free element, but save pointer to next element first.
    struct Person *next = list->current->next;
    free(list->current);
    // Set new current element
    list->current = next;
}
void PrintPerson(struct Person *person)
{
    printf("Person with ID %d:\n", person->id);
    printf("\tName: %s\n", person->name);
    printf("\tAge: %d\n\n", person->age);
}

/**
 * Add a person to the list
 *
 * @param list, a pointer to the list of people
 * @param name, the name of the person being added
 * @param age, the age of the person being added
 * @param last_unique_id, the last unique id used
 */
void AddPerson(struct List * list, char name[50], int age, int * last_unique_id)
{
    list->count++; // Increase the count of people in the list
    (*last_unique_id)++; // Make a new unique id

    /**
     * Create the person, assign its member variables, and add it to the list
     */
    struct Person* person = (struct Person *) malloc(sizeof(struct Person));

    // If allocation failed, print error
    if (person == NULL) {
        printf("ERROR: Out of memory, malloc person failed with AddPerson\n");
        exit(0);
    }

    person->id = *last_unique_id;
    strncpy(person->name, name, 50);
    person->age = age;
    ListInsert(list, person);
}

/**
 * Find a person from the list of people
 *
 * @param list, a pointer to the list of people
 * @param unique_id, the unique id of the person
 */
void FindPerson(struct List * list, int unique_id)
{
    /**
     * Let the user know if the person cannot be found.
     * Otherwise, print the user data.
     */
    ListFind(list, unique_id);
    if (ListGet(list) == NULL) {
        printf("A person with such an unique ID was not found! \n");
    } else {
        PrintPerson(ListGet(list));
    }
}

/**
 * Remove a person from the list of people
 *
 * @param list, a pointer to the list of people
 * @param unique_id, the unique id of the person to remove
 */
void RemovePerson(struct List * list, int unique_id)
{
    /**
     * Let the user know if the person cannot be found.
     * Otherwise, remove the person.
     */
    ListFind(list, unique_id);
    if (ListGet(list) == NULL) {
        printf("A person with such an unique ID was not found to remove! \n");
    } else {
        list->count--; // Decrease the count of people in the list
        ListRemove(list);
    }
}

/**
 * Print the people in the list
 *
 * @param list, a pointer to the list of people
 */
void PrintList(struct List *list) {

    ListHead(list);

    /**
     * Let the user know if the list is empty.
     * Otherwise, print each person in the list.
     */
    if(list->count == 0)
        printf("There's nothing in the list! \n");
    else {
        int i;
        for(i = 0; i < list->count; i++) {
            PrintPerson(ListGet(list));
            ListNext(list);
        }
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
    printf("1. Add a person\n" );
    printf("2. Find a person\n" );
    printf("3. Remove a person\n" );
    printf("4. Print the list\n" );
    printf("5. Sort the list by age\n" );
    printf("6. Sort the list by name\n" );
    printf("7. Exit\n\n" );
    printf("Select an option: " );

    // Scan a digit from the user
    scanf("%d", &sel);

    // Return the chosen digit
    return sel;
}

/**
 * Run the navigational loop
 *
 * @param list, a pointer to the list of people
 * @param last_unique_id, the last unique id used
 * @return Number on exit. 0 for no errors.
 */
int Run(struct List * list, int * last_unique_id)
{
    int sel, person_age, unique_id;
    char person_name[50];

    // While true
    while(true) {

        // Print the menu and get a selection
        sel = PrintMenu();
        ListHead(list);

        // Next step depends on the selection made
        switch(sel) {

            // User chose 1
            case 1:
                printf("You selected \"Add a person\"\n");
                printf("Name of person: ");
                scanf("%48s", person_name);

                printf("Age of person: ");
                scanf("%d", &person_age);
                printf("\n");

                AddPerson(list, person_name, person_age, last_unique_id);
                break;

            // User chose 2
            case 2:
                printf("You selected \"Find a person\"\n");
                printf("Unique ID of person to find: ");
                scanf("%d", &unique_id);
                FindPerson(list, unique_id);
                break;

            // User chose 3
            case 3:
                printf("You selected \"Remove a person\"\n");
                printf("Unique ID of person to remove: ");
                scanf("%d", &unique_id);
                RemovePerson(list, unique_id);
                break;

            // User chose 4
            case 4:
                printf("You selected \"Print the list\"\n");
                PrintList(list);
                break;

            // User chose 5
            case 5:
                printf("You selected \"Sort the list by age\"\n");
                sortByAge(list, last_unique_id);
                break;

            // User chose 6
            case 6:
                printf("You selected \"Sort the list by name\"\n");
                sortByName(list, last_unique_id);
                break;

            // User chose 7
            case 7:
                printf("You selected \"Exit\"\n");

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
 * Get an array of the linked list
 *
 * @param list, a pointer to the list of people
 * @return An array of People structs
 */
struct Person ** getArrayOfPeople(struct List * list)
{
    /**
     * Allocate some space for a 2D array of People.
     * Free in return function.
     */
    ListHead(list);
    struct Person ** array_of_people =
        (struct Person **) malloc(list->count * sizeof(struct Person *));
    if(list->count == 0)
        return NULL;
    else {
        /**
         * Add the People pointers to the array
         */
        int i;
        for(i = 0; i < list->count; i++) {
            array_of_people[i] = ListGet(list);
            ListNext(list);
        }
        return array_of_people;
    }
    ListHead(list); // Reset list head
}

/**
 * Sort the people in the list by name
 *
 * @param list, a pointer to the list of people
 */
void sortByName(struct List * list, int * last_unique_id)
{

    struct Person ** a = getArrayOfPeople(list);

    int n = list->count;
    int i, j;
    struct Person * temp;

    for (i = 0 ; i < ( n - 1 ); i++)
    {
        for (j = 0 ; j < n - i - 1; j++)
        {
            if (strncmp(a[j+1]->name, a[j]->name, 50) > 0)
            {
                temp   = a[j];
                a[j]   = a[j+1];
                a[j+1] = temp;
            }
        }
    }

    free(list);

    int * temp_last_unique_id;
    *temp_last_unique_id = 0;

    struct List * new_list = malloc(sizeof(struct List));
    ListInitialize(new_list);

    for(i = 0; i < n; i++) {
        *temp_last_unique_id = a[i]->id - 1;
         AddPerson(new_list, a[i]->name, a[i]->age, temp_last_unique_id);
    }
    *list = *new_list;
    free(a);
}

/**
 * Sort the people in the list by age
 *
 * @param list, a pointer to the list of people
 */
void sortByAge(struct List * list, int * last_unique_id)
{

    struct Person ** a = getArrayOfPeople(list);

    int n = list->count;
    int i, j;
    struct Person * temp;

    for (i = 0 ; i < ( n - 1 ); i++)
    {
        for (j = 0 ; j < n - i - 1; j++)
        {
            if (a[j]->age < a[j+1]->age)
            {
                temp      = a[j];
                a[j]   = a[j+1];
                a[j+1] = temp;
            }
        }
    }

    free(list);

    int * temp_last_unique_id;
    *temp_last_unique_id = 0;

    struct List * new_list = malloc(sizeof(struct List));
    ListInitialize(new_list);

    for(i = 0; i < n; i++) {
        *temp_last_unique_id = a[i]->id - 1;
         AddPerson(new_list, a[i]->name, a[i]->age, temp_last_unique_id);
    }
    *list = *new_list;
    free(a);
}

/**
 * Will create and process a linked list
 *
 * @return Number on exit. 0 for no errors.
 */
int main()
{
    int * last_unique_id;
    *last_unique_id = 0;

    struct List * list = malloc(sizeof(struct List));
    ListInitialize(list);

    // Run the loop
    Run(list, last_unique_id);

    return 0;
} //end main
