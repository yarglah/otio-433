/*
	Thierry raspberry|github@yar-glah.org 2016
*/

#include <RCSwitch.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "OTIO.h"

/* Internal globlas */
static RCSwitch otio_cmd = RCSwitch(); // initialisation
static unsigned int otio_device_ID = 0;
static unsigned char *otio_codes = NULL;
static int otio_inited = 0;

int otio_init(const char *modelID, unsigned int deviceID, unsigned char gpio_pin_send, unsigned char gpio_pin_recv) {
 
	otio_codes = NULL;
	
	if (strncmp(modelID, OTIO_09HA01, strlen(OTIO_09HA01)) == 0)
		otio_codes = (unsigned char *) otio_09HA01_codes;
	if (strncmp(modelID, OTIO_09HA02, strlen(OTIO_09HA02)) == 0)
		otio_codes = (unsigned char *) otio_09HA02_codes;
		
	if (otio_codes == NULL)
		return -1;
		
	otio_device_ID = deviceID;
	
	//Serial.begin(9600);
	otio_cmd.enableTransmit(gpio_pin_send);
	otio_cmd.enableReceive(gpio_pin_recv);	
	otio_cmd.setProtocol(2); // par defaut le protocole utilisé est le 1, mais les commandes OTIO utilisent le 2
	otio_cmd.setRepeatTransmit(15); // on repete la transmission 15 fois pour etre sur qu'elle arrive bien
	otio_cmd.setPulseLength(700);
	
	otio_inited = 1;
	
	return 0;
}

OTIO_COMMAND otio_recv(unsigned long timeout) {
	if (otio_inited == 0)
		return UNDEFINED;
	
	for (unsigned long t = 0; t < timeout; t++) {
		if (otio_cmd.available()) {

			unsigned long value = otio_cmd.getReceivedValue();

			otio_cmd.resetAvailable();
			
			if (value != 0) {
				unsigned char command = (unsigned char) value >> 24;
				
				for (int i = 0; i < OTIO_COMMANDS_MAX; i++) {
					if (otio_codes[i] == command) {
						return (OTIO_COMMAND) i;
					}
				}
			}

			printf("NOT DEFINED 0x%X...\n", value);
			
			return UNDEFINED;
		}
		else {
			printf("NOT AVAILABLE...\n");
		}
		sleep(1);
	}
		
	return UNDEFINED;
}

int otio_send(OTIO_COMMAND command_code) {
	if (otio_inited == 0)
		return -1;

	// 32: 32  bits mode
	otio_cmd.send(otio_codes[command_code] >> 24 + otio_device_ID, 32);
	
	return 0;
}


