int power(int x, unsigned int n) {
    if (n==0) return 1;

    int sum = x;
    for (int i=2; i <= n; i++) {
        sum *= x;
    }

    return sum;
}