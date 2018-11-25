#include "stdaup.h"
#define STRING_LENGTH_SEARCH_LIMIT 99

char** prepare_equation(int argc, char** argv);
void remove_dots(char *number);
// void remove_sign(char *number);
char merge_arithmetic_operator(char operator, char sign);

int count_dots(char *number);

int min(int x, int y);
int max(int x, int y);
int difference(int x, int y);
int str_len(char *str);

int main(int argc, char **argv) {
    // Mindestens ein Argument, sonst Abbruch
    if (argc < 2) return -1;

    char** equation = prepare_equation(argc, argv);

    for (int i = 0; i < (argc / 2) + (argc % 2); i++) {
        printf("(%d) %s\n", i, equation[i]);
    }

    return 0;
}

char** prepare_equation(int argc, char** argv) {
    char **equation = calloc((argc / 2) + (argc % 2), sizeof(char*));
    char lastOperator = '+';

    // Gleichung vorbereiten
    for (int i = 1; i < argc; i++) {
        if (i % 2 == 0) { // Jedes Argument mit geradem Index d.h. 2,4,6... ist ein Operator
            lastOperator = argv[i][0];
        } else { // Jedes Argument mit ungeradem Index d.h. 1,3,5... ist eine Zahl
            char merged_sign = merge_arithmetic_operator(lastOperator, argv[i][0] == '-' ? '-' : '+');
            int targetIndex = i / 2;

            if (argv[i][0] == '+' || argv[i][0] == '-') {
                equation[targetIndex] = calloc(str_len(argv[i]) + 1, sizeof(char));

                for (int j = 0; j <= str_len(argv[i]); j++) {
                    equation[targetIndex][j] = argv[i][j];
                }

                equation[targetIndex][0] = merged_sign;
            } else {
                equation[targetIndex] = calloc(str_len(argv[i]) + 2, sizeof(char));

                for (int j = 0; j <= str_len(argv[i]); j++) {
                    equation[targetIndex][j + 1] = argv[i][j];
                }

                equation[targetIndex][0] = merged_sign;
            }

            remove_dots(equation[targetIndex]);        
        }
    }

    return equation;
}

char* addition(char* numberA, char* numberB) {
    
}

int is_bigger(char* number, char* compared) {}

// Findet den Index des Kommas in einer Zahl
int find_comma_index(char *number) {
    for (int i=1; i < str_len(number); i++) {
        if (number[i] == ',') return i;
    }

    return -1;
}

// Zählt die Punkte '.' in der Gleichung
int count_dots(char *number) {
    int count = 0;

    for (int i=1; i < str_len(number); i++) {
        if (number[i] == '.') count++;
    }

    return count;
}

// Entfernt alle '.' aus der Gleichung, die machen später nur Probleme
void remove_dots(char *number) {
    int j = 0;
    int curPoints = 0;
    while(number[j] != '\0') {
        if (number[j] == '.') curPoints++;
        else number[j - curPoints] = number[j];
        j++;
    }
    number[j - curPoints] = '\0';
}

// Vereinigt arithmetische Operatoren d.h. + -a -> - a; + +a -> + a; - -a -> + a
char merge_arithmetic_operator(char operator, char sign) {
    if (operator != sign) return '-';
    else return '+';
}

// Gibt den kleineren der beiden Werte zurück
int min(int x, int y) {
    if (x < y) return x;
    else return y;
}

// Gibt den größeren der beiden Werte zurück
int max(int x, int y) {
    if (x > y) return x;
    else return y;
}

// Gibt die Differenz zwischen den beiden Werten zurück
int difference(int x, int y) {
    return max(x, y) - min(x, y);
}


// Hilfsfunktion - Gibt die Länge des gegeben Strings zurück ohne das NUL-Byte
int str_len(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        if (len > STRING_LENGTH_SEARCH_LIMIT) {
            printf("ERROR: Suchbereichende erreicht. Kein \\0 (NUL-Byte) gefunden.\n");
            return 0;
        }
        len++;
    }
    return len;
}
