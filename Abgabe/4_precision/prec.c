#include "stdaup.h"
#define STRING_LENGTH_SEARCH_LIMIT 99

char** prepare_equation(int argc, char** argv);
void remove_dots(char *number);
char merge_arithmetic_operator(char operator, char sign);

int find_comma_index(char *number);

char abs_compare(char* numberA, char* numberB);
char* abs_addition(char* numberA, char* numberB, char operator);

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
            // printf("abs_compare: (%d) %c (%d)\n", i - 1, abs_compare(equation[i - 1], equation[i]), i);
            printf("abs_addition: (%d) + (%d) = %s\n", i - 1, i, abs_addition(equation[i-1], equation[i], '+'));
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
        // else return abs_subtraction(numberA, numberB, '-'); // Negative Zahl minus negative Zahl - d.h. Betragsabs_addition mit negativem Vorzeichen.
    } else {
        char comparation = abs_compare(numberA, numberB);
        if (comparation == '=') {
            // TODO: 0 als Ergebnis zurückgeben.
        } else if (comparation == '>') { // Wenn die erste Zahl größer ist und...
            if (numberB[0] == '-') {
                // return abs_subtraction(numberA, numberB, '+'); // ... dieser eine kleinere Zahl abgezogen wird
            } else {
                // return abs_subtraction(numberB, numberA, '-'); // ... dieser eine kleinere positive Zahl hinzugefügt wird
            }
        } else { // Wenn die zweite Zahl größer ist und...
            if (numberB[0] == '-') {
                // return abs_subtraction(numberB, numberA, '-'); // ... diese minus gerechnet wird von einer kleineren positiven Zahl
            } else {
                // return abs_subtraction(numberB, numberA, '+'); // ... diese zu einer kleineren negativen Zahl plus gerechnet wird
            }
        }
    }

    printf("ERROR: Noch nicht gehandelter Fall wurde aufgerufen.\n");
    return "";
}

char* abs_addition(char* numberA, char* numberB, char operator) {
    printf("numberA: %s|\n", numberA);
    printf("numberB: %s|\n", numberB);

    int lengthA = str_len(numberA);
    int lengthB = str_len(numberB);

    int commaIndexA = find_comma_index(numberA);
    int commaIndexB = find_comma_index(numberB);

    printf("commaIndexA: %d\n", commaIndexA);
    printf("commaIndexB: %d\n", commaIndexB);

    int fragmentalDigitsCountA = lengthA - (commaIndexA);
    if (fragmentalDigitsCountA > 0) fragmentalDigitsCountA--;

    int fragmentalDigitsCountB = lengthB - (commaIndexB);
    if (fragmentalDigitsCountB > 0) fragmentalDigitsCountB--;

    int fragmentalDigitsCountDifference = difference(fragmentalDigitsCountA, fragmentalDigitsCountB);

    printf("fragmentalDigitsCountA: %d\n", fragmentalDigitsCountA);
    printf("fragmentalDigitsCountB: %d\n", fragmentalDigitsCountB);

    int addedComma = fragmentalDigitsCountA > 0 || fragmentalDigitsCountB > 0 ? 1 : 0;

    int result_size = max(commaIndexA, commaIndexB) + max(fragmentalDigitsCountA, fragmentalDigitsCountB) + addedComma + 3;
    printf("result_size: %d\n", result_size);
    char* result = calloc(result_size, sizeof(char));


    int index = result_size - 3;
    printf("starting index: %d\n", index);
    int indexA = lengthA - 1;
    int indexB = lengthB - 1;

    for (int i = 0; i < result_size; i++) {
      result[i] = '~';
    }

    for (int i = 0; i < fragmentalDigitsCountDifference; i++) {
      if (fragmentalDigitsCountA > fragmentalDigitsCountB) {
        result[index] = numberA[indexA];
        printf("Übernehme ein Digit von A für index=%d.\n", index);
        printf("Digit: %c\n", numberA[indexA]);
        indexA--;
      } else {
        result[index] = numberB[indexB];
        printf("Übernehme ein Digit von B für index=%d.\n", index);
        printf("Digit: %c\n", numberB[indexB]);
        indexB--;
      }

      index--;
    }

    printf("============\n");

    int carry = 0;

    while (index > 0) {
        if (numberA[indexA] == ',' || numberB[indexB] == ',') {
          result[index] = ',';
          printf("result[%d]=\',\'\n", index);

          indexA--;
          indexB--;
          index--;
          continue;
        }
        int digitA;
        if (indexA <= 0) digitA = 0;
        else digitA = numberA[indexA] - '0';
        printf("indexA: %d\n", indexA);
        printf("digitA: %d\n", digitA);

        int digitB;
        if (indexB <= 0) digitB = 0;
        else digitB = numberB[indexB] - '0';
        printf("indexB: %d\n", indexB);
        printf("digitB: %d\n", digitB);

        int digitResult = digitA + digitB + carry;
        printf("digitResult: %d\n", digitResult);

        carry = digitResult / 10;
        printf("carry: %d\n", carry);
        digitResult = digitResult % 10;
        result[index] = digitResult + '0';
        printf("result[%d]=%c\n", index, result[index]);

        index--;
        indexA--;
        indexB--;
    }


    printf("index: %d\n", index);
    printf("indexA: %d\n", indexA);
    printf("indexB: %d\n", indexB);

    // while(index > 0) {
    //     printf("numberA[indexA=%d]: %c\n", indexA, numberA[indexA]);
    //     printf("numberB[indexB=%d]: %c\n", indexB, numberB[indexB]);
    //     if (numberA[indexA] == ',') indexA--;
    //     if (numberB[indexB] == ',') indexB--;
    //
    //     if (indexA > lengthA) {
    //         result[index] = numberA[indexA];
    //     } else if (indexB > lengthA) {
    //         result[index] = numberB[indexB];
    //     } else {
    //         int digitA = numberA[indexA] - '0';
    //         printf("digitA: %d\n", digitA);
    //         int digitB = numberB[indexB] - '0';
    //         printf("digitB: %d\n", digitB);
    //         int digitResult = digitA + digitB + carry;
    //         printf("digitResult: %d\n", digitResult);
    //
    //         carry = digitResult / 10;
    //         printf("carry: %d\n", carry);
    //         digitResult = digitResult % 10;
    //         result[index] = digitResult + '0';
    //     }
    //
    //     index--;
    //     indexA--;
    //     indexB--;
    // }

    // TODO: Nochmal überprüfen. Irgendwas stimmt hier nicht. Ich hab das im Gefühl.
    printf("carry ist %d\n", carry);
    if (carry > 0) {
      for (int i=0; i <= result_size - 2; i++) {
        result[i + 1] = result[i];
      }

      result[1] = carry + '0';
      printf("result[1] ist %c\n", result[1]);
      result[result_size - 1] = '\0';
    } else {
      result[result_size - 2] = '\0';
    }

    result[0] = operator;
    return result;
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
