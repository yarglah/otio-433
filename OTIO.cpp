/*
	Thierry raspberry|github@yar-glah.org 2016
*/

#include <RCSwitch.h>
#include <string.h>
#include <unistd.h>
#include "OTIO.h"

/* Internal globals */
static RCSwitch otio_cmd = RCSwitch(); // initialisation
static unsigned int otio_device_ID = 0;
static const OTIO_CODES *otio_codes = NULL;
static int otio_inited = 0;

int otio_init(const char *modelID, unsigned int deviceID, unsigned char gpio_pin_send, unsigned char gpio_pin_recv) {
 
	otio_codes = NULL;

	for (unsigned int i = 0; i < (sizeof(all_otio_codes) / sizeof(OTIO_CODES)); i++) {
		if (strcmp(modelID, all_otio_codes[i].model_ID) == 0)
			otio_codes = &(all_otio_codes[i]);
	}

	if (otio_codes == NULL)
		return -1;
	
	otio_device_ID = deviceID;
	
	otio_cmd.enableTransmit(gpio_pin_send);
	otio_cmd.enableReceive(gpio_pin_recv);	
	otio_cmd.setProtocol(2); // OTIO use 2
	otio_cmd.setRepeatTransmit(15);
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
					if (otio_codes->codes[i] == command) {
						return (OTIO_COMMAND) i;
					}
				}
			}

			return UNDEFINED;
		}

		sleep(1);
	}
		
	return UNDEFINED;
}

int otio_send(OTIO_COMMAND command_code) {
	if (otio_inited == 0)
		return -1;

	// 32: 32  bits mode
	otio_cmd.send(otio_codes->codes[command_code] >> 24 + otio_device_ID, 32);
	
	return 0;
}


