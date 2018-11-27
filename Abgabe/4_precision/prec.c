#include "stdaup.h"
#define STRING_LENGTH_SEARCH_LIMIT 99

char** prepare_equation(int argc, char** argv);
void remove_dots(char *number);
// void remove_sign(char *number);
char merge_arithmetic_operator(char operator, char sign);

int find_comma_index(char *number);
int count_dots(char *number);

char abs_compare(char* numberA, char* numberB);
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
        if (i > 0) {
            printf("abs_compare: (%d) %c (%d)", i - 1, abs_compare(equation[i - 1], equation[i]), i);
        }
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

char* solve(char* numberA, char* numberB) {
    if (numberA[0] == numberB[0]) {
        if (numberB[0] == '+') return abs_addition(numberA, numberB, '+'); // positive Zahl plus positive Zahl - d.h. Betragsabs_addition mit positivem Vorzeichen.
        else return abs_subtraction(numberA, numberB, '-'); // Negative Zahl minus negative Zahl - d.h. Betragsabs_addition mit negativem Vorzeichen.
    } else {
        char comparation = abs_compare(numberA, numberB);
        if (comparation == '=') {
            // TODO: 0 als Ergebnis zurückgeben.
        } else if (comparation == '>') { // Wenn die erste Zahl größer ist und...
            if (numberB[0] == '-') {
                return abs_subtraction(numberA, numberB, '+'); // ... dieser eine kleinere Zahl abgezogen wird
            } else {
                return abs_subtraction(numberB, numberA, '-'); // ... dieser eine kleinere positive Zahl hinzugefügt wird
            }
        } else { // Wenn die zweite Zahl größer ist und...
            if (numberB[0] == '-') { // ... diese minus gerechnet wird von einer kleineren positiven Zahl
                return abs_subtraction(numberB, numberA, '-');
            } else {
                return abs_subtraction(numberB, numberA, '+'); // ... diese zu einer kleineren negativen Zahl plus gerechnet wird
            }
        }
    }
}

char* abs_addition(char* numberA, char* numberB) {
    int lengthA = str_len(numberA);
    int lenghtB = str_len(numberB);

    char* result = calloc(max(lengthA, lenghtB), sizeof(char));

    int commaIndexA = find_comma_index(numberA);
    int commaIndexB = find_comma_index(numberB);

    
}

// Vergleicht den Betrag zweier Zahlen.
char abs_compare(char* numberA, char* numberB) {
    if (find_comma_index(numberA) == find_comma_index(numberB)) {
        int lengthA = str_len(numberA);
        int lengthB = str_len(numberB);

        for (int i = 1; i < min(lengthA, lengthB); i++) {
            if (numberA[i] > numberB[i]) return '>';
            if (numberA[i] < numberB[i]) return '<'; // Wenn eine der bei beiden vorhanden Stelle größer oder kleiner ist.
        }
        
        if (lengthA > lengthB) return '>'; // Wenn alle bei beiden vorhanden Stellen identisch sind und eine Zahl mehr Stellen besitzt, dann ist sie größer.
        if (lengthA < lengthB) return '<'; // Vorraussetzung: Zahlen enden nicht auf reduntanten Nullen -> EBNF in Aufgabenstellung.

        return '=';
    }
    else if (find_comma_index(numberA) > find_comma_index(numberB)) return '>';
    else return '<'; // Wenn der Kommaindex sich unterscheidet, dann ist die Zahl mit mehr Vorkommastellen größer.
}

// Findet den Index des Kommas in einer Zahl
int find_comma_index(char *number) {
    for (int i=1; i < str_len(number); i++) {
        if (number[i] == ',') return i;
    }

    return str_len(number);
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

// Hilfsfunktion - Gibt den kleineren der beiden Werte zurück
int min(int x, int y) {
    if (x < y) return x;
    else return y;
}

// Hilfsfunktion - Gibt den größeren der beiden Werte zurück
int max(int x, int y) {
    if (x > y) return x;
    else return y;
}

// Hilfsfunktion - Gibt die Differenz zwischen den beiden Werten zurück
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
