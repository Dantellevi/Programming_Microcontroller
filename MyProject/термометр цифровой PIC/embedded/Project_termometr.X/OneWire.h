/* 
 * File:   OneWire.h
 * Author: Dante_L_Levi
 *
 * Created on 25 апреля 2018 г., 21:59
 */

#ifndef ONEWIRE_H
#define	ONEWIRE_H

#include "Main.h"
#include <string.h>


#define MATCH_ROM	0x55
#define SKIP_ROM	0xCC
#define	SEARCH_ROM	0xF0

#define CONVERT_T	0x44		// DS1820 commands
#define READ		0xBE
#define WRITE		0x4E
#define EE_WRITE	0x48
#define EE_RECALL	0xB8

#define	SEARCH_FIRST	0xFF		// start new search
#define	PRESENCE_ERR	0xFF
#define	DATA_ERR	0xFE
#define LAST_DEVICE	0x00		// last device found
//			0x01 ... 0x40: continue searching


#define W1_PIN PORTCbits.RC0
#define W1_IN  RC0
#define W1_OUT PORTCbits.RC0
#define W1_DDR TRISC0



//=================================Прототипы функций================
/*
 =============================Функция передачи команды==============
 */
void OneWire_Command(uint8_t command,uint8_t *id);
/*
 ============================Функция получения кода устройства===========
 */
uint8_t OneWire_ROM_Search(uint8_t diff,uint8_t *id);
/*
 ================Функция чтения байта===============
 */
uint16_t OneWire_Byte_RD(void);
/*
 =========================Функция записи байта=========
 */
uint16_t OneWire_byte_WR(uint8_t b);
/*
 ====================Чтение запись бита==============
 */
uint8_t OneWire_bit_IO(uint8_t b);
/*
 =================Функция перезапуска интерфейса======
 */
uint8_t oneWire_Reset(void);




#endif	/* ONEWIRE_H */

