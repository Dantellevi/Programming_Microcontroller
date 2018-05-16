#include "USART.h"


#define ANY 0

unsigned int cSend = 0;   // счетчик отправленных символов


inline void uart_init(unsigned int baud)  // Функция инициализаций UART'a (синтаксис uart_init(9600))
{
	#if F_CPU < 2000000UL && defined(U2X)
	UCSRA =(1<<U2X);             // если частота ниже 2 МГц, для устранения удваиваем скорость
	UBRRL = (F_CPU / (8UL * baud)) - 1;
	#else
	UBRRL = (F_CPU / (16UL * baud)) - 1;
	#endif
	UCSRB =(1<<TXEN) |(1<<RXEN); // включаем прием/передачу
}

inline void uart_putc(unsigned char data) // Функция отправки одного символа (байта) (синтаксис uart_putc('a'))
{
	
	while ( !( UCSRA & (1<<UDRE) ) ); // ждем пока освободится регистр UDR
	UDR = data;						   // начинаем передачу
	if (data != 8)
	cSend++; // увеличиваем счетчик отправленных символов
	else
	cSend--; // если отослали backspace уменьшаем счетчик отправленных символов
}

inline unsigned char uart_getc (void) // функция принятия 1-го символа (байта)
{
	while ( !(UCSRA & (1<<RXC)) );   // ждем прихода символа
	return UDR;						  // получаем результат
}

inline void uart_write (char *str)	// функция передачи строки
{
	for(int i = 0; str[i]; ++i)
	uart_putc(str[i]);
}

inline void uart_write_int(unsigned int val)
{
	char str[MAX_LINE_LENGHT];
	itoa(val, str, 10); // преобразим значение val в строку
	uart_write(str);	 // отправим строку
}

inline char *uart_readln(char *s)
{
	char ch, *p;
	int t;

	p = s;  /* uart_readln() возвращает указатель s */

	for(t=0; t<MAX_LINE_LENGHT; ++t){
		ch = uart_getc();  // получаем символ
		uart_putc(ch);		// для наглядности отправляем назад
		switch(ch) {
			case '\r':
			s[t] = '\0'; /* завершает строку */
			return p;
			case 0x08:
			if(t>0) t--;
			break;
			default:
			s[t] = ch;
		}
	}
	s[MAX_LINE_LENGHT - 1] = '\0';
	return p;
}

inline int CharToInt(char ch)
{
	if ((ch >= '0') && (ch <= '9')) // если символ число
	return ch - '0';			  // делаем преобразование
	else
	return -1; 					  // иначе возвращаем 1
}

inline void uart_clr(unsigned int l)
{
	for(int i = cSend - l; i >= 0 ; i--)
	{
		uart_putc(8);
	}
}

inline void uart_wait(char *msg, char k) // функция которая ожидает нажатия клавиши
{
	uart_write(msg);                     // вывод сообщения
	while(uart_getc() != k);			 // ждем нажатия клавиши k
	
}