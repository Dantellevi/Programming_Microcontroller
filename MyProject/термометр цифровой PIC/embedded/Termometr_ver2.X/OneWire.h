/* 
 * File:   OneWire.h
 * Author: Dante_L_Levi
 *
 * Created on 28 февраля 2018 г., 19:23
 */

#ifndef ONEWIRE_H
#define	ONEWIRE_H

#include "Main.h"


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
#define W1_PIN_PORT PORTC
#define W_TRIS TRISC0
#define OWIREINPIN RC0

#define TRISWIREINPUT  W_TRIS=1
#define TRISWIREOUT    W_TRIS=0


#define SETPINWIRE W1_PIN=1
#define RESETPINWIRE W1_PIN=0






uint8_t OneWire_reset(void);
uint8_t OneWire_Bit_IO(uint8_t b);
uint16_t OneWire_Byte_Write(uint8_t b);
uint8_t w1_rom_search( uint8_t diff, uint8_t *id );
void OneWire_command( uint8_t command, uint8_t *id );
uint16_t OneWire_Byte_Read(void);





#endif	/* ONEWIRE_H */

