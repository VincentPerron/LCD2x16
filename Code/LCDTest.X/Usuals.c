#include "Usuals.h"

char Int2Char(int number) {
    char text;
    return text = number + '0';
}

// Fonction pour la minuterie 1ms
volatile unsigned long nb_ms = 0;

void InitMin1ms() {
    _T5IF = 0;
    _T5IE = 1;
    _T5IP = 3;
    PR5 = 999;
    T5CON = 0x8010;
}

void _ISRFAST __attribute__((auto_psv)) _T5Interrupt(void) {
    if (nb_ms > 0) --nb_ms;
    _T5IF = 0;
}

void Delai(int ms) {
    nb_ms = ms;
    while (nb_ms > 0);
}