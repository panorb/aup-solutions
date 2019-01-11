#include "stdaup.h"

unsigned long ringshift(unsigned long v, unsigned short b, unsigned short k);
unsigned long maxringshift(unsigned long v, unsigned short b, unsigned short l);
unsigned long maxringshift_step(unsigned long v, unsigned short b, unsigned short l, int s);

int digit_count(unsigned long v, unsigned short b);
unsigned long my_pow(unsigned short b, int p);

// Aufgabe 1
unsigned long ringshift(unsigned long v, unsigned short b, unsigned short k) {
    // Errechnung der Stellenzahl von v in b
    int d_count = digit_count(v, b);

    unsigned long result = 0;

    for (int i = 0; i < d_count; i++) { // d_count
        int digit = v % b;
        v = v / b;

        int d_worth = i;

        // Anpassen der Wertigkeit der ausgelesenen Stelle, wenn sie Teil des Ringshifts ist.
        if (i == k || i == k - 1) {
            d_worth = i + 1;
        } else if (i == k + 1) {
            d_worth = i - 2;
        }

        // Stelle mit entsprechendem Stellenwert wieder in Ergebnis im 10er-System einrechnen
        result = result + (digit * my_pow(b, d_worth));
    }

    return result;
} 

// Aufgabe 2
unsigned long maxringshift(unsigned long v, unsigned short b, unsigned short l) {
    return maxringshift_step(v, b, l, 0);
}

unsigned long maxringshift_step(unsigned long v, unsigned short b, unsigned short l, int s) {
    if (s >= l) return v;
    
    // Errechnung der Stellenzahl von v in b
    int d_count = digit_count(v, b);

    // Zahlen mit weniger als 3 Stellen sollen wie dreistellig behandelt werden, siehe Aufgabenstellung
    if (d_count < 3) d_count = 3;

    unsigned long max_number = v;

    // Alle Stellen, an denen der ringshift vorgenommen werden kann, werden durchgegangen
    for (int i = 1; i <= d_count - 2; i++) {
        unsigned long shift_result = ringshift(v, b, i);
        unsigned long rec_result = maxringshift_step(shift_result, b, l, s+1);
        
        // Die Ergebnisse aller weiteren moeglichen ringshifts in den weiteren Rekursionsebenen werden verglichen
        if (rec_result > max_number) max_number = rec_result;
    }

    return max_number;
}

// Hilfsfunktion - Gibt die Anzahl der Stellen zurueck, die das Ergebnis der Konversation hat.
int digit_count(unsigned long v, unsigned short b) {
    int digit_count = 0;

    while (v > 0) {
        v = v / b;
        digit_count++;
    }

    return digit_count;
}

// Hilfsfunktion - Errechnet b hoch p
unsigned long my_pow(unsigned short b, int p) {
    if (p == 0) return (unsigned long)1;

    unsigned long result = b;
    for (int i = 2; i <= p; i++) {
        result = result * b;
    }

    return result;
}