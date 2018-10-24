#include <stdio.h>

// Declaration
unsigned int sum(unsigned int);
unsigned int sumOdd(unsigned int);
unsigned int digits(unsigned int);
unsigned int checksum1(unsigned int);

int main(int argc, char const *argv[])
{
    printf("sum(%d) = %d\n", 3, sum(3));
    printf("sumOdd(%d) = %d\n", 3, sumOdd(3));
    printf("digits(%d) = %d\n", 3, digits(3));
    printf("checksum1(%d) = %d\n", 3, digits(3));
    return 0;
}
