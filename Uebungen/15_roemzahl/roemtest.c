#include<stdio.h>

unsigned int rom2arab(char);

int main() {
    printf("Hi.");
    char rom[] = "XVI";
    printf("ALLES IST BÖSE!");
    printf("%s in arab is %d", rom, rom2arab(*rom));
}