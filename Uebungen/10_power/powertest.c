#include <stdio.h>

// Declaration
unsigned int power(int, unsigned int);
unsigned int poly1(int, unsigned int);
unsigned int polyAlter(int, unsigned int);

int main(int argc, char const *argv[])
{
    printf("power(%d, %d) = %d\n", 3, 4, power(3, 4));
    printf("poly1(%d, %d) = %d\n", 2, 3, poly1(2, 3));
    printf("manual poly1(2,3): power(2,0) + power(2,1) + power(2,2) + power(2,3) = %d\n", power(2,0) + power(2,1) + power(2,2) + power(2,3));
    printf("polyAlter(%d, %d) = %d\n", 2, 3, polyAlter(2, 3));
    printf("manual polyAlter(2,3): power(2,0) - power(2,1) + power(2,2) - power(2,3) = %d\n", power(2,0) - power(2,1) + power(2,2) - power(2,3));
    return 0;
}
