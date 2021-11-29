#include<stdio.h>
#define INFINITY __INT_MAX__

int main()
{
    int a = -INFINITY;
    // int b = -INFINITY;

    printf("a = %d\n", a);
    // printf("b = %d\n", b);

    return 0;
}