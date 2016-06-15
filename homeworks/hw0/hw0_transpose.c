#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/** Reference used:
 * http://www.programiz.com/c-programming/examples/matrix-transpose
*/

// Predeclare functions
void printMatrix(int ** mat, int r, int c);
void indexTranspose(int ** mat, int r, int c);
void pointerTranspose(int ** mat, int r, int c);
int PrintMenu();
int Run(int ** mat, int r, int c);
int Finalize(int ** mat, int r, int c);

/**
 * Prints the matrix
 *
 * @param mat Int** representing the matrix
 * @param r Int representing the row size
 * @param c Int representing the column size
 */
void printMatrix(int ** mat, int r, int c)
{
    /**
     * Loops through and prints the numbers
     * in the matrix.
     */
    int i, j;
    printf("Printed matrix: \n");
    for(i = 0; i < r; ++i) {
        for(j = 0; j < c; ++j)
        {
            printf("%d  ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Transposes the matrix. The original matrix
 * that is sent in changes to the transpose.
 *
 * @param mat Int** representing the matrix
 * @param r Int representing the row size
 * @param c Int representing the column size
 */
void indexTranspose(int ** mat, int r, int c)
{
    /**
     * Transposes the matrix. Uses a temporary
     * matrix the hold the values of the transpose.
     */
     int temp[r][c];
     int i, j;
     for(i = 0; i < r; ++i)
         for(j = 0; j < c; ++j)
         {
             temp[j][i] = mat[i][j];
         }

     for(i = 0; i < r; ++i)
         for(j = 0; j < c; ++j)
         {
             mat[i][j] = temp[i][j];
         }
}

/**
 * Transposes the matrix. The original matrix
 * that is sent in changes to the transpose.
 * Uses pointer arithmetic.
 *
 * @param mat Int** representing the matrix
 * @param r Int representing the row size
 * @param c Int representing the column size
 */
void pointerTranspose(int ** mat, int r, int c)
{
    /**
     * Transposes the matrix. Uses a temporary
     * matrix the hold the values of the transpose.
     */
     int temp[r][c];
     int i, j;
     for(i = 0; i < r; ++i)
         for(j = 0; j < c; ++j)
         {
             *(*(temp+j)+i) = *(*(mat+i)+j);
         }

     for(i = 0; i < r; ++i)
         for(j = 0; j < c; ++j)
         {
             *(*(mat+i)+j) = *(*(temp+i)+j);
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
    printf("1. Transpose of 3x3 matrix using array indices\n" );
    printf("2. Transpose of 3x3 matrix using only pointers\n" );
    printf("3. Exit\n\n" );
    printf("Select an option: " );

    scanf("%d", &sel); // Scan a digit from the user

    return sel; // Return the chosen digit
}

/**
 * Run the navigational loop
 *
 * @param mat Int** representing the matrix
 * @param r Int representing the row size
 * @param c Int representing the column size
 * @return Number on exit. 0 for no errors.
 */
int Run(int ** mat, int r, int c)
{
    int sel;

    // While true
    while(true) {

        // Print the menu and get a selection
        sel = PrintMenu();

        // Next step depends on the selection made
        switch(sel) {

            // User chose 1
            case 1:
                printMatrix(mat, r, c);
                indexTranspose(mat, r, c);
                printf("After Transpose:\n");
                printMatrix(mat, r, c);
                return 0;
                break;

            // User chose 2
            case 2:
                printMatrix(mat, r, c);
                pointerTranspose(mat, r, c);
                printf("After Transpose:\n");
                printMatrix(mat, r, c);
                return 0;
                break;

            // User chose 3
            case 3:
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
 * Free all the malloced memory
 *
 * @param mat Int** representing the matrix
 * @param r Int representing the row size
 * @param c Int representing the column size
 * @return Number on exit. 0 for no errors.
 */
int Finalize(int ** mat, int r, int c)
{
    int i;
    for(i = 0; i < r; i++)
        free(mat[i]);
    free(mat);

    return 0;
}

/**
 * Provides two functions that can compute the sum
 * or the difference using bitwise logical operators.
 *
 * @return Number on exit. 0 for no errors.
 */
int main()
{
    int const r = 3, c = 3;

    int ** mat;
    int i, j;
    mat = (int **) malloc(r * sizeof(int *));
    for(i = 0; i < r; i++)
            mat[i] = (int *) malloc(c * sizeof(int));

    for(i = 0; i < r; ++i)
        for(j = 0; j < c; ++j)
        {
            printf("Value for [%d][%d]: ", i, j);
            scanf("%d", &mat[i][j]); // Scan a digit from the user
        }
    printf("\n");

    Run(mat, r, c);
    Finalize(mat, r, c);

} //end main
