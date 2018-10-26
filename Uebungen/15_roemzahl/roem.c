#include<stdio.h>

unsigned int rom2arab(char);
unsigned int *arab2rom(unsigned int);

int main() {
   char rom[] = "VXI";
   rom2arab(*rom);
}

unsigned int rom2arab(char *rom) {
    int length = sizeof(*rom) / sizeof(char);
    printf("Length of rom is %d\n");
}

char *arab2rom(unsigned int arab) {

}
