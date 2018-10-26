#include<stdio.h>

unsigned int rom2arab(char *rom) {
    unsigned int sum = 0;
    printf("rom is %p\n", rom);
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
        printf("rom is now %p\n", rom);
        printf("rom value %c\n", *rom);
    }

    return sum;
}

char *arab2rom(unsigned int arab) {
    unsigned int numM = arab / 1000;
    arab %= 1000;

    unsigned int numD = arab / 500;
    arab %= 500;

    unsigned int numC = arab / 100;
    arab %= 100;

    unsigned int numL = arab / 50;
    arab %= 50;

    unsigned int numX = arab / 10;
    arab %= 10;

    unsigned int numV = arab / 5;
    arab %= 5;

    unsigned numCharacters = numM + numD + numC + numL + numX + numV + arab + 1;
    char rom[] = "" + numM * 'M' + numD * 'D' + numC * 'C' + numL * 'L' + numX * 'X' + numV * 'V' + arab * 'I' + '\0';
    return rom;
    // Ich bin zu müde. Ich muss mir das morgen nochmal anschauen.
}