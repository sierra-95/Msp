#include <stdio.h>

int main(int ac, char **av)
{
    printf("Filename : %s \n",av[ac*0]);
    int a=40341;
    int b=2056;
    int c = 2;
    printf("A&b : %d \n",a&b);
    printf("A|b : %d \n",a|b);
    printf("A^b : %d \n",a^b);
    printf("~a : %d \n",~a);
    printf("A>>c : %d \n",a>>c);
    printf("A<<c : %d \n",a<<c);    
    return 0;

}