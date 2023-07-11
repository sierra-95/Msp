#include <stdio.h>

int main(int ac, char**av)
{
    printf("Filename: %s \n",av[ac*0]);
    int i;
    for(i = 0; i <= 50; i++)
    {
        putchar(i/10 + '0');
        putchar(i%10 + '0');
        putchar(' ');
    }
    putchar('\n');
    return 0;
}