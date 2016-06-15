#include <stdio.h>
void printResults(char *chptr);
int main(void)
{
    char ch = 'T';
    //char *chptr;
    char *chptr = &ch;


    int a = 1000;
    int *intptr = &a;

    float fnumber = 1.20000;
    float *fptr = &fnumber;

    char *ptr = "My dog has fleas!";

    printf("\n [%c],[%d],[%f],[%c],[%s]\n", *chptr, *intptr, *fptr, *ptr, ptr);

    chptr = ptr;

    printResults(chptr);

    return 0;
}
void printResults(char *chptr)
{
    char ch2 = 'J';
    char *ptr2=0;
    char name[7];
    printf("\n [%c],[%s], [%c]\n", *chptr, chptr, *ptr2);

    name[0] = 75;
    name[1] = 105;
    name[2] = 0x6d;
    name[3] = 0141;
    name[4] = 0x6e;
    name[5] = 0151;
    name[6] = 0;

    printf("\n [%s]\n", name);
}
