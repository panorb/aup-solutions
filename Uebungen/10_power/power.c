int power(int x, unsigned int n) {
    if (n == 0) return 1;

    int sum = x;
    for (int i = 2; i <= n; i++) {
        sum *= x;
    }

    return sum;
}

int poly1(int x, unsigned int n) {
    int sum = 0;
    for (int i = 0; i <= n; i++) {
        sum += power(x, i);
    }
    
    return sum;
}

int polyAlter(int x, unsigned int n) {
    int sum = 0;
    for (int i = 0; i <= n; i++) {
        sum += power(-1, i) * power(x, i);
    }

    return sum;
}
