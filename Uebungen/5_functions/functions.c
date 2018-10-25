#include <stdio.h>

// Definition
unsigned int sum(unsigned int n) {
    unsigned int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

unsigned int sumOdd(unsigned int n) {
    unsigned int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (n % 2 != 0) sum += i;
    }
    return sum;

}

unsigned int digits(unsigned int n) {
    unsigned int sum = 0;
    while (n != 0) {
        n = n / 10;
        sum++;
    }
    return sum;
}

unsigned int checksum1(unsigned int n) {
    unsigned int sum = 0;
    
    char str[12];
    sprintf(str, "%d", n);

    for (int i=0; i < digits(n) - 1; i++) {
        sum += (int)str[i] - 48;
    }
    return sum;
}