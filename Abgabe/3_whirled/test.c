int printf(const char * restrict, ...);

int a[] = {1, 2, 3, 4}; 
char b[] = "Hallo";

int main(int carg, const char **varg) {
	
	char curChar = varg[1][0];
	char newChar;

	if (carg >= 2) printf("%d\n", curChar);
	else printf("FALSCH\n");

	printf("Länge: %d\n", (sizeof(b) / sizeof(char)));


	if (curChar >= 65 && curChar <= 90) {
		newChar = 90 - (curChar - 65);
    } else if (curChar >= 97 && curChar <=122) {
        newChar = 122 - (curChar - 97);
    }

	printf("%c -> %c\n", curChar, newChar);
}