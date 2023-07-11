#include <stdio.h>
int main (int ac, char **av)
{
    printf("Filename: %s \n",av[ac*0]);
    int i;
    while(i <= 50)
    {
        printf(" 1 to %d \n",i-1);
        putchar(i/10 + '0');
        putchar(i%10 + '0');
        putchar(' ');
        i++;
    }
    putchar('\n');
    return 0;
}