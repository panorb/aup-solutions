#include<stdio.h>

unsigned int rom2arab(char *rom) {
    unsigned int sum = 0;
    printf("rom is %p", rom);
    while (*rom != '\0') {
        if (*rom == 'M') sum += 1000;
        else if (*rom == 'D') sum += 500;
        else if (*rom == 'C') sum += 100;
        else if (*rom == 'L') sum += 50;
        else if (*rom == 'X') sum += 10;
        else if (*rom == 'V') sum += 5;
        else if (*rom == 'I') sum += 1;
        else return 0;

        rom++;
        printf("rom is now %p", rom);
        printf("rom value %c", *rom);
    }

    return sum;
}
