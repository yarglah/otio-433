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

#include <RCSwitch.h>
#include <string.h>
#include "OTIO.h"

OTIO::OTIO(const char *modelID, unsigned long *deviceIDs, unsigned char nbDevices, unsigned char gpio_pin_send, unsigned char gpio_pin_recv)
{
	// Check it's an handled model.
	for (unsigned int i = 0; i < (sizeof(all_otio_codes) / sizeof(OTIO_CODES)); i++) {
		if (strcmp(modelID, all_otio_codes[i].model_ID) == 0) {
			otio_codes = &(all_otio_codes[i]);
			break;
		}
	}

	if (otio_codes != NULL) {
		otio_device_IDs = (unsigned long *) malloc(nbDevices * sizeof(unsigned long));
		memcpy((void *) otio_device_IDs, (void *) deviceIDs, nbDevices * sizeof(unsigned long));
		otio_nbDevices = nbDevices;

		otio_cmd_send = RCSwitch();
		otio_cmd_recv = RCSwitch();

		if (gpio_pin_send != 0) {
			otio_cmd_send.enableTransmit(gpio_pin_send);
			otio_cmd_send.setProtocol(2); // OTIO use 2
			otio_cmd_send.setRepeatTransmit(10);
		}

		if (gpio_pin_recv != 0) {
			otio_cmd_recv.enableReceive(digitalPinToInterrupt(gpio_pin_recv));	
		}
		
		otio_inited = 1;
	}
}

OTIO_COMMAND OTIO::recv() {
	OTIO_COMMAND commandCode = UNKNOWN;

	if (otio_inited != 0)
	{
		if (otio_cmd_recv.available()) {
			unsigned long value = otio_cmd_recv.getReceivedValue();
			if (value != 0) {
				unsigned char command = (unsigned char) (value >> 24);
				unsigned long deviceID = value & 0xFFFFFF;
				bool found = false;
				
				for (int i = 0; i < otio_nbDevices && found == false; i++) {
					if (deviceID == otio_device_IDs[i]) {
						for (int i = 0; i < OTIO_COMMANDS_MAX; i++) {
							if (otio_codes->codes[i] == command) {
								commandCode = (OTIO_COMMAND) i;
								delay(200); // Avoid duplicates
								found = true;
								break;
							}
						}
					}
				}
/*
				Serial.print("OTIO received: 0x");
				Serial.print(value, HEX);
*/
			}
			otio_cmd_recv.resetAvailable();		
		}
	}
	
	return commandCode;	
}

OTIO_COMMAND OTIO::recv(unsigned long timeout) {
	if (otio_inited == 0)
		return UNKNOWN;
	
	for (unsigned long t = 0; t < timeout; t++) {
		OTIO_COMMAND command = UNKNOWN;

		command = recv();
		if (command != UNKNOWN)
			return command;

		delay(500);
	}
		
	return UNKNOWN;
}

int OTIO::send(OTIO_COMMAND command_code) {
	if (otio_inited == 0)
		return -1;

	unsigned long codeToSend = otio_codes->codes[command_code];
	codeToSend <<= 24;
	codeToSend += otio_device_IDs[0];
	// Delay is before sending command to avoid interference with remote control signal sent directly to end devices.
	delay(100);
	otio_cmd_send.send(codeToSend, 32);
	delay(100);
	otio_cmd_recv.resetAvailable();
	
	return 0;
}

unsigned long OTIO::getID(unsigned char gpio_pin_recv) {
	unsigned long ID = 0;
	static RCSwitch otio_cmd_recv;

	otio_cmd_recv.enableReceive(digitalPinToInterrupt(gpio_pin_recv));	
	
	if (otio_cmd_recv.available()) {
		ID = (otio_cmd_recv.getReceivedValue() & 0xFFFFFF);
		otio_cmd_recv.resetAvailable();
		delay(300);
	}
	
	return ID;
}