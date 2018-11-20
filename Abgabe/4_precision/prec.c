#include "stdaup.h"

char* removePoints(const char * const number);
int str_len(const char * const str);
int str_len_step(int *len, const char * const str);

int main(int argc, char const *argv[])
{
    if (argc != 2) return 0;

    const char* number = argv[1];
    printf("Ohne .: \"%s\"", removePoints(number));

    return 0;
}

// Removes all points from the equation
char* removePoints(const char * const number) {
    int i = 0;
    int totalPoints = 0;
    while(number[i] != '\0') {
        if (number[i] == '.') totalPoints++;
        i++;
    }
    
    char* res[str_len(number) + 1 - totalPoints];
    res[str_len(number) - totalPoints] = '\0';

    int j = 0;
    int curPoints = 0;
    while(number[j] != '\0') {
        if (number[j] == '.') curPoints++;
        else res[j - curPoints] = number[j];
        j++;
    }

    return res;
}
/* 
int vorkommazahl(char *number) {

} */

// Hilfsfunktion - Gibt die Länge des gegeben Strings zurück ohne das NUL-Byte
int str_len(const char * const str) {
    int len = 0;
    return str_len_step(&len, str);
}

// Rekursiver Teil der Hilfsfunktion
int str_len_step(int *len, const char * const str) {
    if (str[*len] == '\0') return *len;
    (*len)++;
    return str_len_step(len, str);
}
