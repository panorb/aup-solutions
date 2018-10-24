#include <stdio.h>

unsigned long int squareroot(unsigned long int);

int main(int argc, char const *argv[])
{
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("sqrt(%d)=%d\n", 3, squareroot(3));
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("sqrt(%d)=%d\n", 75, squareroot(75));
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    return 0;
}
