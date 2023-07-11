#include <stdio.h>
#define i


void green();
void red();
int main()
{
    green();
    printf("cow \n");
    return 0;
    
}

void green(){
    int p=0;	
    while(p<10)
    {
       
        printf("%d",p);
        p++;
    }
	
}
