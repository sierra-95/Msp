#include <stdio.h>

int main(int ac, char **av)
{
    printf("Filename:%s \n",av[ac*0]);
    char grade;
    printf("Please enter your grade:\n");
    scanf("%c",&grade);
    switch(grade){
        case 'A':
           printf("You did good \n");
           break;
        case 'B':
           printf("Nice \n"); 
           break;  
        case 'C':
           printf("You can do better \n");
           break;
        case 'D':
           printf("Pull up your socks \n");     
           break;  
        default:
           printf("Invalid grade \n");   
    }
   
    return 0;
}