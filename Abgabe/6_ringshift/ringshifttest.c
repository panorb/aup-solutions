// #include "ringshift.c"
#include <stdio.h>

unsigned long ringshift(unsigned long v, unsigned short b, unsigned short k);
unsigned long maxringshift(unsigned long v, unsigned short b, unsigned short l);
// unsigned long my_pow(unsigned short b, int p);

// TESTFUNKTIONEN
// void pow_test(unsigned short b, int p);

// void print_binary(int number)
// {
//     if (number) {
//         print_binary(number >> 1);
//         putc((number & 1) ? '1' : '0', stdout);
//     }
// }

// void ringshift_test(unsigned long v, unsigned short b, unsigned short k) {
//     printf("before: ");
//     print_binary(v);
//     printf("\n");
    
//     unsigned long result = ringshift(v, b, k);
//     printf("after: ");
//     print_binary(result);
//     printf("\n");
// }

int main(/* int argc, char const *argv[] */) {
    /*
    |* POW-TEST
    */
    // pow_test(3, 3);
    // pow_test(3, 4);
    // pow_test(2, 5);
    // pow_test(2, 2);
    // pow_test(13, 0);
    // pow_test(24, 1);

    // ringshift(12, 10, 2);
    
    printf("ringshift(1234, 10, 2) = %lu\n", ringshift(1234, 10, 2));
    printf("ringshift(1234, 2, 3) = %lu\n", ringshift(1234, 2, 3));
    printf("ringshift(1000, 23, 1) = %lu\n", ringshift(1000, 23, 1));
    printf("+-+-+-+-+-+-+\n");
    printf("maxringshift(1234, 10, 5) = %lu\n", maxringshift(1234, 10, 5));
    printf("maxringshift(5, 2, 8) = %lu\n", maxringshift(5, 2, 8));
    printf("maxringshift(5, 10, 5) = %lu\n", maxringshift(5, 10, 5));
    printf("maxringshift(15, 3, 3) = %lu\n", maxringshift(15, 3, 3));

    return 0;
}

// void pow_test(unsigned short b, int p) {
//     printf("%d hoch %d = %lu\n", b, p, my_pow(b, p));
// }
