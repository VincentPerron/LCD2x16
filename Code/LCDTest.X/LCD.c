#include "LCD.h"

char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void LCD_Init() {
    int i;
    int LCD_INIT_STRING[4] = {0x28, 0x0C, 0X01, 0X06};
    RS = INST;
    RW = WRITE;
    E = false;

    for (i = 1; i <= 3; ++i) {
        LCD_Enable(FUNCT_SET_8bit);
        Delai(5);
    }

    LCD_Enable(FUNCT_SET_4bit);
    Delai(5);

    for (i = 0; i <= 3; ++i) LCD_Send(INST, LCD_INIT_STRING[i]);
}

void LCD_Enable(int caract) {
    // Modifier cette ligne si les DB4 a DB7 ne sont pas sur RB12 a RB15;
    LATB = ((LATB & 0x0FFF) | (caract << 12));
    E = true;
    asm("repeat #12"); // délai 300ns
    asm("nop");
    E = false;
}

void LCD_Send(int RegSelect, int caract) {
    Delai(1);
    RS = RegSelect;
    LCD_Enable(caract >> 4); //Envoie des 4 bits MSB
    LCD_Enable(caract & 0x0F); // Envoie des 4 bits LSB
}

void PlaceCursor(int position) {
    position |= 0x80;
    LCD_Send(INST, position);
}

void LCD_Write(char *buffer) {
    while (*buffer != '\0') {
        LCD_Send(DATA, *buffer++);
    }
}