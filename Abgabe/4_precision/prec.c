#include "stdaup.h"
#define STRING_LENGTH_SEARCH_LIMIT 250

char** prepare_equation(int argc, char** argv);
void remove_dots(char *number);
char merge_arithmetic_operator(char operator, char sign);

int count_integer_digits(char *number);

char* solve(char* numberA, char* numberB);

char abs_compare(char* numberA, char* numberB);
char* abs_computation(char operation, char* numberA, char* numberB, char operator);
int digit_computation(char operation, int fragmentals, char* result, char* numberA, char* numberB, int index, int indexA, int indexB, int lengthA, int lengthB, int carry);

int count_fragmental_digits(char* number);
int min(int x, int y);
int max(int x, int y);
int str_len(char *str);

void prepare_result(char* result);

int main(int argc, char **argv) {
    if (argc < 2) return -1; // Mindestens ein Argument, sonst Abbruch

    char** equation = prepare_equation(argc, argv);
    char* result = equation[0];

    for (int i = 0; i < argc / 2; i++) {
        if (i > 0) {
            char* new_result = solve(result, equation[i]);
            free(result);
            result = new_result;
        }
    }

    prepare_result(result);
    printf("%s\n", result);
    free(result);
    return 0;
}

void prepare_result(char* result) {
    int hasComma = count_fragmental_digits(result);
    int length = str_len(result);
    int endingZeros = 0;

    // Überflüssige Endnullen entfernen und wenn Komma dann alleine steht auch dieses entfernen
    if (hasComma) {
        for (int i = length - 1; i > 1; i--) {
            if (result[i] == '0') endingZeros++;
            else break;
        }

        length = length - endingZeros;
        if (result[length - 1] == ',') length--;
        
        result[length] = '\0';
    }

    // Überflüssiges '+' als Vorzeichen entfernen
    if (result[0] == '+') {   
        for (int i=1; i <= length; i++) {
            result[i-1] = result[i];
        }
    }

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
        if (numberB[0] == '+') return abs_computation('+', numberA, numberB, '+'); // positive Zahl plus positive Zahl - d.h. Betragsabs_addition mit positivem Vorzeichen.
        else return abs_computation('+', numberA, numberB, '-'); // Negative Zahl minus negative Zahl - d.h. Betragsabs_addition mit negativem Vorzeichen.
    } else {
        char comparation = abs_compare(numberA, numberB);
        if (comparation == '=') {
            char* result = calloc(3, sizeof(char));
            result[0] = '+'; result[1] = '0'; result[2] = '\0';
            return result;
        } else if (comparation == '>') { // Wenn die erste Zahl größer ist und...
            if (numberB[0] == '-') {
                return abs_computation('-', numberA, numberB, '+'); // ... dieser eine kleinere Zahl abgezogen wird
            } else {
                return abs_computation('-', numberA, numberB, '-'); // ... dieser eine kleinere positive Zahl hinzugefügt wird
            }
        } else { // Wenn die zweite Zahl größer ist und...
            if (numberB[0] == '-') {
                return abs_computation('-', numberB, numberA, '-'); // ... diese minus gerechnet wird von einer kleineren positiven Zahl
            } else {
                return abs_computation('-', numberB, numberA, '+'); // ... diese zu einer kleineren negativen Zahl plus gerechnet wird
            }
        }
    }
}

char* abs_computation(char operation, char* numberA, char* numberB, char operator) {
    int lengthA = str_len(numberA);
    int lengthB = str_len(numberB);
    
    int integerDigitsA = count_integer_digits(numberA);
    int integerDigitsB = count_integer_digits(numberB);
    
    int fragmentalDigitsA = count_fragmental_digits(numberA);
    int fragmentalDigitsB = count_fragmental_digits(numberB);

    int aHasComma = fragmentalDigitsA > 0 ? 1 : 0;
    int bHasComma = fragmentalDigitsB > 0 ? 1 : 0;
    int resultHasComma = aHasComma > 0 || bHasComma > 0 ? 1 : 0;

    int resultLength = 1 // 1 Char für das übergebene Vorzeichen.
        + max(integerDigitsA, integerDigitsB) // Maximum an Vorkommastellen der beiden Zahlen
        + resultHasComma // 1 Char für das evtl. vorhandene Komma
        + max(fragmentalDigitsA, fragmentalDigitsB) // Maximum der evtl. vorhandenen Nachkommastellen der beiden Zahlen
        + 1; // Freigehaltenes Char für den eventuellen Überlauf

    char* result = calloc(
        resultLength
        + 1 // Das NUL-Byte
        , sizeof(char));

    for (int i = 0; i < resultLength - 1; i++) {
        result[i] = '~';
    }

    result[0] = operator;
    result[resultLength - 1] = '\0'; // NUL-Byte; muss bei Überlauf mit verschoben werden
    
    int index = resultLength
        - 1 // Arrays beginnen bei Null zu zählen
        - 1; // Freigehaltenes Char wird nur bei Überlauf beschrieben, indem der ganze Inhalt des Arrays verschoben wird

    int indexA = integerDigitsA // Vorkommastellen
        + 1 // evtl. vorhandenes Komma
        + max(fragmentalDigitsA, fragmentalDigitsB); // Maximum der evtl. vorhandenen Nachkommastellen

    int indexB = integerDigitsB // Vorkommastellen
        + 1 // evtl. vorhandenes Komma
        + max(fragmentalDigitsA, fragmentalDigitsB); // Maximum der evtl. vorhandenen Nachkommastellen

    /*
    |* NACHKOMMASTELLENRECHNUNG
    */
    int carry = 0; // Übertragsvariable; wird in die Stellenberechnung einbezogen
    if (resultHasComma) {
        while (index > max(integerDigitsA, integerDigitsB) + 1) { // Überprüfen ob noch im Kommabereich, nur bei einer Zahl notwendig
            carry = digit_computation(operation, 1, result, numberA, numberB, index, indexA, indexB, lengthA, lengthB, carry);

            index--;
            indexA--;
            indexB--;
        }

        result[index] = ',';
        index--;
    }

    indexA--;
    indexB--;

    /*
    |* VORKOMMASTELLENRECHNUNG
    */
    while (index > 0) {
        carry = digit_computation(operation, 0, result, numberA, numberB, index, indexA, indexB, lengthA, lengthB, carry);

        index--;
        indexA--;
        indexB--;
    }

    /*
    |* ÜBERLAUFBEHANDELUNG
    */
    if (operation == '+' && carry) {
        for (int i = resultLength; i > 1; i--) {
            result[i] = result[i - 1];
        }

        result[1] = carry + '0';
    }
    
    return result;
}

int digit_computation(char operation, int fragmentals, char* result, char* numberA, char* numberB, int index, int indexA, int indexB, int lengthA, int lengthB, int carry) {
    int digitA;
    if ((fragmentals && indexA < lengthA) || (!fragmentals && indexA > 0)) digitA = numberA[indexA] - '0';
    else digitA = 0;

    int digitB;
    if ((fragmentals && indexB < lengthB) || (!fragmentals && indexB > 0)) digitB = numberB[indexB] - '0';
    else digitB = 0;

    int digitResult;

    if (operation == '+') {
        digitResult = digitA + digitB + carry;

        if (digitResult >= 10) {
            carry = 1;
            digitResult -= 10;
        } else carry = 0;
    } else {
        digitResult = digitA - digitB - carry;

        if (digitResult < 0) {
            carry = 1;
            digitResult += 10;
        } else carry = 0;
    }

    result[index] = digitResult + '0';
    return carry;
}

int count_fragmental_digits(char* number) {
    for (int i = 0; i < str_len(number); i++) {
        if (number[i] == ',') {    
            return str_len(number) - count_integer_digits(number) - 1 - 1; // -1 für das Vorzeichen; -1 für das Komma
        }
    }

    return 0;
}

// Vergleicht den Betrag zweier Zahlen.
char abs_compare(char* numberA, char* numberB) {
    if (count_integer_digits(numberA) == count_integer_digits(numberB)) {
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
    else if (count_integer_digits(numberA) > count_integer_digits(numberB)) return '>';
    else return '<'; // Wenn der Kommaindex sich unterscheidet, dann ist die Zahl mit mehr Vorkommastellen größer.
}

// Findet den Index des Kommas in einer Zahl
int count_integer_digits(char *number) {
    for (int i=1; i < str_len(number); i++) {
        if (number[i] == ',') return i - 1; // -1 für das Vorzeichen
    }

    return str_len(number) - 1; // -1 für das Vorzeichen
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

// Hilfsfunktion - Gibt die Länge des gegeben Strings zurück ohne das NUL-Byte
int str_len(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
