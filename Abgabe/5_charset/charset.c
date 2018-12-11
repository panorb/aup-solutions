#include "stdaup.h"
#include "charset.h"

void charset_set(charset_t* s, int bitIndex);
void charset_unset(charset_t* s, int bitIndex);
int charset_get(const charset_t* s, int bitIndex);
int str_len(const char *str);
int charset_enabled_count(const charset_t* s);

// Aufgabenfunktion: Diese Funktion legt einen neue Menge vom Typ charset_t, die aus den Elementen des
// übergebenen Strings elements besteht, als anonyme Variable an, und gibt einen Zeiger auf diese neue
// Menge zurück. Sollte elements Zeichen enthalten, die keine Buchstaben sind, werden diese Zeichen ignoriert.
charset_t *charset_new(const char* elements) {
    charset_t* set = malloc(sizeof(charset_t));

    for (int i = 0; i < 7*8; i++) charset_unset(set, i);
    
    for (int i = 0; i < str_len(elements); i++) {
        char cur = elements[i];
        int bitIndex;

        if ('A' <= cur && cur <= 'Z') {
            bitIndex = ((cur - 'A') * 2);
        } else if ('a' <= cur && cur <= 'z') {
            bitIndex = ((cur - 'a') * 2) + 1;
        } else continue;

        charset_set(set, bitIndex);
    }
    return set;
}

// Aufgabenfunktion: Diese Funktion verknpüft die beiden übergebenen Mengen mit der durch op beschriebenen
// Operation und gibt das Ergebnis in der ersten Menge zurück. s1 ist also sowohl Operand als auch Ziel
// der Operation.
// Der Rückgabewert der Funktion ist im Erfolgsfall 0, bei inkorrekten Parametern (Nullzeigern oder ungültigen
// Werten für op) ist er -1.
int charset_op(charset_t* s1, const charset_t *s2, csopt_t op) {
    if (!s1 || !s2) return -1;

    switch (op) {
        case CS_UNION:
            for (int i = 0; i <= 7; i++) {
                s1->bits[i] = s1->bits[i] | s2->bits[i];
            }
            return 0;
        case CS_CUT:
            for (int i = 0; i <= 7; i++) {
                s1->bits[i] = s1->bits[i] & s2->bits[i];
            }
            return 0;
        case CS_SYMDIFF:
            for (int i = 0; i <= 7; i++) {
                s1->bits[i] = s1->bits[i] ^ s2->bits[i];
            }
            return 0;
        default:
            return -1;
    }
}

// Aufgabenfuntion: Diese Funktion gibt für die übergebene Menge s einen (weiternutzbaren) String zurück, der
// genau die Elemente von s geordnet (alphabetisch, jeweiliger Großbuchstabe vor dem ensprechendem Kleinbuch-
// staben) enthält.
char *charset_tos(const charset_t* s) {
    char* str = calloc(charset_enabled_count(s) + 1, sizeof(char));

    int i = 0;

    for (int j = 0; j < 52; j++) {
        if (charset_get(s, j)) {
            int odd = j % 2;
            if (odd)
                str[i] = ((j - 1) / 2) + 'a';
            else
                str[i] = (j / 2) + 'A';       
            i++;
        }
    }

    str[i] = '\0';
    return str;
}

// Gibt die Anzahl der Einser in den Charset-Bytes zurück
int charset_enabled_count(const charset_t* s) {
    int count = 0;

    for (int i = 0; i < 52; i++) {
        if (charset_get(s, i)) count++;
    }

    return count;
}

// Setzt das Bit an der angegebenen Stelle auf 1
void charset_set(charset_t* s, int bitIndex) {
    int byteIndex = bitIndex / 8;
    int bitIndexInByte = bitIndex % 8;
    
    s->bits[byteIndex] |= ((char) 1) << (7 - bitIndexInByte);
}

// Setzt das Bit an der angegebenen Stelle auf 0
void charset_unset(charset_t* s, int bitIndex) {
    int byteIndex = bitIndex / 8;
    int bitIndexInByte = bitIndex % 8;

    s->bits[byteIndex] &= ~(((char) 1) << (7 - bitIndexInByte));
}

// Gibt 1 oder 0 zurück, entsprechend dem Bit an der angegebenen Stelle.
int charset_get(const charset_t* s, int bitIndex) {
    int byteIndex = bitIndex / 8;
    int bitIndexInByte = bitIndex % 8;

    return (s->bits[byteIndex] >> (7 - bitIndexInByte)) & ((char) 1);
}

// Hilfsfunktion - Gibt die Länge des gegeben Strings zurück ohne das NUL-Byte
int str_len(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
