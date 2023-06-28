/*
Documentation section
C programming structure
Author: **** */
/* Preprocessor section */
#include <stdio.h>
/* Global declaration, definition section */
int subtract = 0;
/* Function declaration section */
int all (int, int);
/* Main function */
int main (){
printf ("This is a C program \n");
subtract= all (25,10);
printf ("Subtraction of the two numbers : %d \n", subtract);
return 0;
}
/* User defined function */
int all (int x, int y) {
return x-y; /* definition section */
}