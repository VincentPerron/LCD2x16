#include "p24FJ64GA002.h"
#include "Usuals.h"

#define     CLR_DISP        1    // Clear display and set AC to 0x00
#define     FUNCT_SET_8bit  3    // 8bits, 2 lines
#define     FUNCT_SET_4bit  2    // 4bits, 2 lines

#define     INST            0
#define     DATA            1
#define     WRITE           0

#define     E               _RB4
#define     RS              _RB6
#define     RW              _RB5

void LCD_Init();
void LCD_Enable(int caract);
void LCD_Send(int RegSelect, int caract);
void PlaceCursor(int position);
void LCD_Write(char *buffer);


