// Definition
unsigned long int _run_guess(unsigned long int, unsigned long int);
unsigned long int _min(unsigned long int, unsigned long int);
unsigned long int _max(unsigned long int, unsigned long int);
unsigned long int _difference(unsigned long int, unsigned long int);

// Deklaration
unsigned long int squareroot(unsigned long int val) {
    if (val == 0) return 0; // Ist Spezialfall 0? Muss gesondert geregelt werden
    return _run_guess(val, 1337); // Ansonsten: Aufrufen des Heron-Algorithmus zur Approximation; Startwert: 1337
}


// Selbstaufrufende Funktion: Führt den Heron-Algorithmus durch
unsigned long int _run_guess(unsigned long int val, unsigned long int guess) {
    unsigned long int last_guess = guess;
    guess = (val / guess + guess) / 2;

    if (_difference(last_guess, guess) <= 1) return guess;

    return _run_guess(val, guess);
}

// Gibt den kleineren der beiden Werte zurück
unsigned long int _min(unsigned long int x, unsigned long int y) {
    if (x < y) return x;
    else return y;
}

// Gibt den größeren der beiden Werte zurück
unsigned long int _max(unsigned long int x, unsigned long int y) {
    if (x > y) return x;
    else return y;
}

// Gibt die Differenz zwischen den beiden Werten zurück
unsigned long int _difference(unsigned long int x, unsigned long int y) {
    return _max(x, y) - _min(x, y);
}
