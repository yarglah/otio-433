/*
  OTIO-433 - Arduino libary for OTIO devices remote control
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

#ifndef _OTIO_CODES_H
#define _OTIO_CODES_H

/* Supported models */
/* To add a new model define a "friendly" identifier and add a new OTIO_CODES to all_otio_codes */
#define OTIO_09HA01	"09HA01"
#define OTIO_09HA02	"09HA02"

// 34 commands
#define OTIO_COMMANDS_MAX 34

typedef struct OTIO_CODES {
   const char *model_ID;
   const unsigned char codes[OTIO_COMMANDS_MAX];
} OTIO_CODES_ST;


/* Note: commands are the same between versions but with a 20 index shift (A01 A1_ON is A02 C3_ON)
Memory may be optimized by code if this assumption is confirmed on other models. 
*/

const OTIO_CODES all_otio_codes[] = {
	{
		OTIO_09HA01,
		{
	/* A */ 	0x20, 0x28, 0x10, 0x18, 0x30, 0x38, 0x8, 0x4,
	/* B */ 	0x2C, 0x22, 0x1C, 0x12, 0x3C, 0x32, 0x2, 0xA,
	/* C */ 	0x26, 0x2E, 0x16, 0x1E, 0x36, 0x3E, 0xE, 0x1,
	/* D */ 	0x29, 0x25, 0x19, 0x15, 0x39, 0x35, 0x5, 0xD,
	/* All */ 	0x13, 0x23
		}
	}, {
		OTIO_09HA02,
		{
	/* A */ 	0x36, 0x3E, 0xE, 0x1, 0x26, 0x2E, 0x16, 0x1E,
	/* B */ 	0x39, 0x35, 0x5, 0xD, 0x29, 0x25, 0x19, 0x15,
	/* C */ 	0x30, 0x38, 0x8, 0x4, 0x20, 0x28, 0x10, 0x18,
	/* D */ 	0x3C, 0x32, 0x2, 0xA, 0x2C, 0x22, 0x1C, 0x12,
	/* All */ 	0x13, 0x23
		}
	}
};

#endif