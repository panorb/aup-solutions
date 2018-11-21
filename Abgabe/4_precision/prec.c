#include "stdaup.h"

char** copy_equation(int argc, char** argv);
void remove_dots(char *number);
void remove_sign(char *number);
char merge_arithmetic_operator(char operator, char sign);

int str_len(char *str);

int main(int argc, char **argv) {
    // Mindestens ein Argument, sonst Abbruch
    if (argc < 2) return -1;

    char lastOperator = '+';

    char** equation = copy_equation(argc, argv);

    // Gleichung vorbereiten
    for (int i = 1; i < argc; i++) {
        if (i % 2 == 0) { // Jedes Argument mit geradem Index d.h. 2,4,6... ist ein Operator
            lastOperator = equation[i][0];
        } else { // Jedes Argument mit ungeradem Index d.h. 1,3,5... ist eine Zahl
            equation[i - 1][0] = merge_arithmetic_operator(lastOperator, equation[i][0] == '-' ? '-' : '+');
            equation[i - 1][1] = '\0'; // Für die erste Zahl wird das nullte Argument d.h. der Programmname überschrieben, das Nullbyte muss dementsprechend neu platziert werden, da Programmname länger als 1 Zeichen ist
            remove_sign(equation[i]); // Vorzeichen aus der Zahl entfernen; dieses wurde ja bereits berücksichtigt.
            remove_dots(equation[i]); // Punkte aus Argumenten entfernen, um später Probleme zu vermeiden
        }
    }

    for (int i = 0; i < argc; i++) {
        printf("(%d) %s\n", i, equation[i]);
    }

    return 0;
}

char** copy_equation(int argc, char** argv) {
    char **equation = calloc(argc, sizeof(char*));
    char *firstOperator = calloc(2, sizeof(char));
    firstOperator[0] = '+';
    firstOperator[1] = '\0';
    equation[0] = firstOperator;

    for (int i = 1; i < argc; i++) {
        equation[i] = calloc(str_len(argv[i]) + 1, sizeof(char));

        for (int j = 0; j <= str_len(argv[i]); j++) {
            equation[i][j] = argv[i][j];
        }
    }

    return equation;
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

void remove_sign(char *number) {
    if (number[0] == '+' || number[0] == '-') {
        for (int i = 1; i <= str_len(number); i++) {
            number[i - 1] = number[i];
        }
    }
}

// Vereinigt arithmetische Operatoren d.h. + -a -> - a; + +a -> + a; - -a -> + a
char merge_arithmetic_operator(char operator, char sign) {
    if (operator != sign) return '-';
    else return '+';
}

// Hilfsfunktion - Gibt die Länge des gegeben Strings zurück ohne das NUL-Byte
int str_len(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        if (len > 99) {
            printf("ERROR: Kein \\0 (NUL-Byte) gefunden.\n");
            return 0;
        }
        len++;
    }
    return len;
}
