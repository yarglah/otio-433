/*
  OTIO-433 - Arduino libary for OTIO remote control devices
  Copyright (c) 2016 Thierry raspberry|github at yar-glah.org
  
  Project home: 
  https://github.com/yarglah/otio-433
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _OTIO_H
#define _OTIO_H

#include "OTIO_codes.h"
#include <RCSwitch.h>

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
	UNKNOWN   = 0xFF
};

class OTIO {
public:
	/* Constructor.
	- modelID: one of OTIO_09x constant
	- deviceID: device unique identifier (command 24 less significant bits)
	- gpio_pin_send: device GPIO pin (RCswitch notation) for transmit
	- gpio_pin_recv: device GPIO pin (RCswitch notation) for reception 
	Returns:
	- 0 on success
	- other on error:
		- -1: for unknown model
	*/
	OTIO(const char *modelID, unsigned long deviceID, unsigned char gpio_pin_send, unsigned char gpio_pin_recv);

	/* Return command code if available, UNDEFINED otherwise */
	OTIO_COMMAND recv();

	/* Return command code until timeout (in seconds), UNDEFINED otherwise */
	OTIO_COMMAND recv(unsigned long timeout);

	/* Send OTIO command */
	int send(OTIO_COMMAND code);
	
	/* Tool to get the device ID, return device ID if signal detected, or 0 */
	unsigned long getID();		

private:
	/* Internal globals */
	RCSwitch otio_cmd_send;
	RCSwitch otio_cmd_recv;
	unsigned long otio_device_ID = 0;
	const OTIO_CODES *otio_codes = NULL;
	int otio_inited = 0;
};

#endif
