#include <p24fj64ga002.h>

#define true 1
#define false 0

char Int2Char(int number);

// Fonction pour la minuterie 1ms
void InitMin1ms();
void _ISRFAST __attribute__((auto_psv)) _T5Interrupt(void);
void Delai(int ms);
