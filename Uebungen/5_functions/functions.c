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

    if (n == 0) return 0;

    for (int i = 1; i <= 1 + 2*(n-1); i+=2) {
        sum += i;
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
    while (n != 0) {
        sum += n % 10;
        n /= 10;
    }

    return sum;
}