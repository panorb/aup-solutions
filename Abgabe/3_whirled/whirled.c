/* AuP WS 2018/19, bewertete Aufgabe 3 */
int printf(const char * restrict, ...);
void *malloc(unsigned long);

const char *whirled(const char * const str); // Deklaration der Aufgabenfunktion
const char *whirled_step(const char * const str, char * const res, int length, int curIndex); // Deklaration meiner rekusriven Funktion.

int str_len(const char * const str); // Deklaration einer Hilfsfunktion zur Bestimmung der Stringlänge
int str_len_step(int *len, const char * const str); // Deklaration meiner rekursiven Funktion für die Bestimmung der Stringlänge

int main(int carg, const char **varg) {
    if (carg != 2) return -1; // ein Parameter uebergeben?
    printf("Die verwürfelte Version von \"%s\" ist \"%s\".\n",
        varg[1], whirled(varg[1])); // gibt Ergebnis aus
    return 0; // 0 bedeutet alles okay
}

// Ihr Code ab hier
// Die geforderte Aufgabenfunktion
const char *whirled(const char * const str) {
    char * const res = malloc(sizeof(char) * (str_len(str) + 1));  
    res[str_len(str)] = '\0';

    whirled_step(str, res, str_len(str), 0);
    return res;
}

// Rekursiver Teil der Aufgabenfunktion
const char *whirled_step(const char * const str, char * const res, int length, int curIndex) {
    char curChar = str[curIndex];
    char newChar;

    if (curChar >= 65 && curChar <= 90) {
	newChar = 90 - (curChar - 65);
    } else if (curChar >= 97 && curChar <= 122) {
        newChar = 122 - (curChar - 97);
    } else {
        newChar = curChar;
    }

    res[length - 1 - curIndex] = newChar;

    curIndex++;
    if (curIndex >= length) return res;
    return whirled_step(str, res, length, curIndex);
}

// Hilfsfunktion - Gibt die Länge des gegeben Strings zurück - des NUL-Bytes
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
