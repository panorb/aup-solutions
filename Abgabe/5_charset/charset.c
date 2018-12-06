#include "stdaup.h"
#include "charset.h"

void charset_set(charset_t* s, int bitIndex);
void charset_unset(charset_t* s, int bitIndex);
int charset_get(const charset_t* s, int bitIndex);
int str_len(const char *str);
int charset_enabled_count(const charset_t* s);


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

int charset_op(charset_t* s1, const charset_t *s2, csopt_t op) {
    switch (op) {
        case CS_UNION:
            for (int i = 0; i < 52; i++) {
                if (charset_get(s1, i) || charset_get(s2, i)) charset_set(s1, i);
            }
            return 0;
        case CS_CUT:
            for (int i = 0; i < 52; i++) {
                if (charset_get(s1, i) && charset_get(s2, i)) charset_unset(s1, i);
            }
            return 0;
        case CS_SYMDIFF:
            for (int i = 0; i < 52; i++) {
                if ((charset_get(s1, i) && !charset_get(s2, i)) || (!charset_get(s1, i) && charset_get(s2, i))) charset_set(s1, i);
                else charset_unset(s1, i);
            }
            return 0;
        default:
            return -1;
    }
}

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

int charset_enabled_count(const charset_t* s) {
    int count = 0;

    for (int i = 0; i < 52; i++) {
        if (charset_get(s, i)) count++;
    }

    return count;
}

void charset_set(charset_t* s, int bitIndex) {
    int byteIndex = bitIndex / 8;
    int bitIndexInByte = bitIndex % 8;
    
    s->bits[byteIndex] |= ((char) 1) << (7 - bitIndexInByte);
}

void charset_unset(charset_t* s, int bitIndex) {
    int byteIndex = bitIndex / 8;
    int bitIndexInByte = bitIndex % 8;

    s->bits[byteIndex] &= ~(((char) 1) << (7 - bitIndexInByte));
}

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
