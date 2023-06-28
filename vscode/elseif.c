#include <stdio.h>
int main()
{
    printf("Enter: \n");
    int a;
    scanf("%d",&a);
    if(a<10)
    {
        printf("less\n");
    }
    else if(a>10 && a<50)
    {
        printf("Medium \n");

    }
    else{
        printf("Large\n");
    }
    return 0;
}