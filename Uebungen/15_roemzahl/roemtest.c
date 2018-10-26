#include<stdio.h>

unsigned int rom2arab(char*);
char *arab2rom(unsigned int);

int main() {
    printf("%s in arab is %d\n", "XVI", rom2arab("XVI"));
    printf("%d in arab is %s\n", 98, arab2rom(98));
}