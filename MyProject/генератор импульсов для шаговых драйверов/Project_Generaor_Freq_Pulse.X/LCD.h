
#ifndef LCD_H
#define	LCD_H

#include "Main.h"
#include <string.h>

#define DDR_COMAND TRISB
#define DDR_DATA   TRISD

#define PORT_COMAND PORTB
#define PORT_DATA   PORTD

#define RS  PORTBbits.RB0   
#define RW  PORTBbits.RB1
#define E   PORTBbits.RB2

    
#define D4  PORTDbits.RD4
#define D5  PORTDbits.RD5
#define D6  PORTDbits.RD6
#define D7  PORTDbits.RD7
    

#define E_SET()     (PORTBbits.RB2=1)
#define E_RESET()   (PORTBbits.RB2=0)
#define RS_COM()    (PORTBbits.RB0=0)
#define RS_DATA()   (PORTBbits.RB0=1)



/*
 ============================Функция передачи данных на дисплей=============
 * Принимаемые параметры:
 * data- данные для выставления в дисплей
 */
void Send_Data(char data);


/*
 ========================Функция передачи команды ======================
 * Принимаемые параметры:
 * com-команда для передачи
 */
void Send_command(char com);


/*
 ==================================Функция Инициализации дислпея===========
 */
void lcd_init(char lcd);


/*
 ============================Функция вывода одного символа========================
 */
void lcd_Print_char(char data);


/*
 ==========================Функция вывода строки символов======================
 */
void lcd_printString(char *str);



/*
 ========================Функция перехода по определенным строками и столбцам===========
 */
void lcd_gotoxy(char x, char y);

/*
 =======================Функция вывода строки по координатам===================
 */
void lcd_printStringXY(char *str,char x,char y);



/*
 ==================================Функция очистки дисплея======================
 */
void lcd_clear(void);




#endif	/* LCD_H */

