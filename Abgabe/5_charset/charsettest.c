#include "stdaup.h"
#include "charset.h"

void print_charset(const charset_t* s);
void print_binary(char byte);

int main() {
    charset_t *s1 = charset_new("AaBbCcDdEe");
    // print_charset(s1);

    charset_t *s2 = charset_new("BbCcYyZz");
    // print_charset(s2);
    
    char *str1 = charset_tos(s1);
    printf("str1=\"%s\"\n",str1); // ergibt: ”aHlo”

    printf("r: %d\n", charset_op(s1,s2,CS_SYMDIFF));
    char *str2 = charset_tos(s1);

    printf("str2=\"%s\"\n",str2); // ergibt: ”AaBbCcHlo”
    free(s1);
    free(s2);
    free(str1);
    free(str2);
    return 0;
}

// void print_charset(const charset_t* s) {
//     for (int i = 0; i < 26; i++) {
//         printf("%c", 'A' + i);
//         printf("%c", 'a' + i);
//     }
    
//     printf("\n");

//     for (int i = 0; i < 7; i++) {
//         print_binary(s->bits[i]);
//     }
//     printf("\n");
// } // Only for testing. Delete later.

// void print_binary(char byte) {
//     printf("%c%c%c%c%c%c%c%c", (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'), (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'), (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'), (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0'));
// } // Only for testing. Delete later.
