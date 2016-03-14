/*
 * Projet: TestLCD
 * Date: 8 mars 2016
 * Auth: Nicolas Toupin
 */

#include "p24FJ64GA002.h"
#include "LCD.h"
#include "Usuals.h"

_CONFIG1(JTAGEN_OFF& GCP_OFF &GWRP_OFF& ICS_PGx2& FWDTEN_OFF& WINDIS_OFF)
_CONFIG2(0x7987)

#define LED _RA1

int sec = 0;
int temp = 0;
char data;

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void) {

    // Mise a jour de la temperature
    PlaceCursor(0x08);
    LCD_Send(DATA, Int2Char(temp / 10));
    PlaceCursor(0x09);
    LCD_Send(DATA, Int2Char(temp % 10));
    ++temp;
    if (temp >= 20) temp = 0;

    // Mise a jour du chauffage
    if (LED == true) {
        PlaceCursor(0x4C);
        LCD_Write("On ");
    } else {
        PlaceCursor(0x4C);
        LCD_Write("OFF");
    }

    _T1IF = 0;
}

void _ISRFAST __attribute__((auto_psv)) _T5Interrupt(void);

int main() {

    AD1PCFG = 0xFFFE;
    TRISA = 0x0001;
    TRISB = 0x0000;

    InitMin1ms();

    T1CON = 0x8030;
    PR1 = 31249;
    _T1IF = 0;
    _T1IP = 1;
    _T1IE = 1;

    Delai(25);

    LCD_Init();

    LCD_Write("Temp. :");

    PlaceCursor(0x0B);

    LCD_Write("oC");

    PlaceCursor(0x40);

    LCD_Write("Chauffage :");

    while (1) {
        Delai(15000);
        LED = ~LED;
        Delai(15000);
    }
}