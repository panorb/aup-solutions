#include <stdio.h>

// Declaration
unsigned int sum(unsigned int);
unsigned int sumOdd(unsigned int);
unsigned int digits(unsigned int);
unsigned int checksum1(unsigned int);

int main(int argc, char const *argv[])
{
    printf("sum(%d) = %d\n", 0, sum(0));
    printf("sumOdd(%d) = %d\n", 0, sumOdd(0));
    printf("digits(%d) = %d\n", 24, digits(24));
    printf("checksum1(%d) = %d\n", 134, checksum1(134));
    return 0;
}
