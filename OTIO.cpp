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

OTIO::OTIO(const char *modelID, unsigned long deviceID, unsigned char gpio_pin_send, unsigned char gpio_pin_recv) {
	// Reset variables
	otio_device_ID = 0;
	otio_codes = NULL;
	otio_inited = 0;
	otio_cmd_send = RCSwitch();
	otio_cmd_recv = RCSwitch();

	for (unsigned int i = 0; i < (sizeof(all_otio_codes) / sizeof(OTIO_CODES)); i++) {
		if (strcmp(modelID, all_otio_codes[i].model_ID) == 0) {
			otio_codes = &(all_otio_codes[i]);
			break;
		}
	}

	if (otio_codes != NULL)
	{
		otio_device_ID = deviceID;
		
		if (gpio_pin_send != 0) {
			otio_cmd_send.enableTransmit(gpio_pin_send);
			otio_cmd_send.setProtocol(2); // OTIO use 2
			otio_cmd_send.setRepeatTransmit(15);
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
				
				if (deviceID == otio_device_ID) {
					for (int i = 0; i < OTIO_COMMANDS_MAX; i++) {
						if (otio_codes->codes[i] == command) {
							commandCode = (OTIO_COMMAND) i;
							delay(300); // Avoid duplicates	
							break;
						}
					}
					/*
						Serial.print("OTIO received: 0x");
						Serial.print(value, HEX);
						Serial.print(" ");
						Serial.print(deviceID, HEX);
						Serial.print(" ");
						Serial.println(command, HEX);
					*/
				}
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

		delay(1000);
	}
		
	return UNKNOWN;
}

int OTIO::send(OTIO_COMMAND command_code) {
	if (otio_inited == 0)
		return -1;
	
	unsigned long codeToSend = otio_codes->codes[command_code];
	codeToSend <<= 24;
	codeToSend += otio_device_ID;
	/*
	Serial.print("OTIO send code:");
	Serial.print(command_code, HEX);
	Serial.print(" 0x");
	Serial.println(codeToSend, HEX);
	*/

	// 32: 32  bits mode
	otio_cmd_send.send(codeToSend, 32);
	
	return 0;
}

unsigned long OTIO::getID() {
	unsigned long ID = 0;
	
	if (otio_cmd_recv.available()) {
		ID = (otio_cmd_recv.getReceivedValue() & 0xFFFFFF);
		delay(500);
		otio_cmd_recv.resetAvailable();
	}
	
	return ID;
}