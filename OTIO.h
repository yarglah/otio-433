/*
	OTIO devices command library
	Thierry raspberry|github@yar-glah.org 2016
*/

#ifndef _OTIO_H
#define _OTIO_H

#include "OTIO_codes.h"

enum OTIO_COMMAND {
	A1_ON 	= 0,
	A1_OFF	= 1,
	A2_ON 	= 2,
	A2_OFF	= 3,
	A3_ON 	= 4,
	A3_OFF	= 5,
	A4_ON 	= 6,
	A4_OFF	= 7,
	B1_ON 	= 8,
	B1_OFF	= 9,
	B2_ON 	= 10,
	B2_OFF	= 11,
	B3_ON 	= 12,
	B3_OFF	= 13,
	B4_ON 	= 14,
	B4_OFF	= 15,
	C1_ON 	= 16,
	C1_OFF	= 17,
	C2_ON 	= 18,
	C2_OFF	= 19,
	C3_ON 	= 20,
	C3_OFF	= 21,
	C4_ON 	= 22,
	C4_OFF	= 23,
	D1_ON 	= 24,
	D1_OFF	= 25,
	D2_ON 	= 26,
	D2_OFF	= 27,
	D3_ON 	= 28,
	D3_OFF	= 29,
	D4_ON 	= 30,
	D4_OFF	= 31,
	GROUP_ON	= 32,
	GROUP_OFF	= 33,
	UNDEFINED   = 0xFF
};

#define OTIO_09HA01	"09HA01"
#define OTIO_09HA02	"09HA02"

/* Initialize library, must be called before any othe function.
- modelID: one of OTIO_09x constant
- deviceID: device unique identifier (command 24 less significant bits)
- gpio_pin_send: device GPIO pin (RCswitch notation) for transmit
- gpio_pin_recv: device GPIO pin (RCswitch notation) for reception 
Returns:
- 0 on success
- other on error:
	- -1: for unknown model
*/
int otio_init(const char *modelID, unsigned int deviceID, unsigned char gpio_pin_send, unsigned char gpio_pin_recv);

/* Return command code until timeout (in seconds), UNDEFINED otherwise */
OTIO_COMMAND otio_recv(unsigned long timeout);

/* Send OTIO command */
int otio_send(OTIO_COMMAND code);

#endif
