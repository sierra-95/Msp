#include <stdio.h>
int main(int ac, char ** av)
{
    printf("Filename: %s",av[ac*0]);
    int i;
    do{
        /*-------WONT RUN*/
        printf("1 to %i",i);
        putchar(i/10 + '0');
        putchar(i%10 + '0');
        putchar(' ');
        i++;
    }while(1 <= 50);
    return 0;
}

