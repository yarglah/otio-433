/*
	Thierry raspberry|github@yar-glah.org 2016
*/


#include <stdio.h>
#include "OTIO.h"

int main(int argc, char *argv[]) {
	//int init = otio_init(OTIO_09HA02, 0x555555, 2, 3);
	int init = otio_init("bla", 0x555555, 2, 3);
	
	if (init == 0) {
		OTIO_COMMAND action = UNDEFINED;
		
		otio_send(A2_OFF);
		
		printf("Press button...\n");
		
		while  (action == UNDEFINED) {
			action = otio_recv(4);
		
			if (action == UNDEFINED) {
				printf("Press button...\n");
			}
			else {
				printf("Received: 0X%uc\n", (unsigned char) action);
			}
		}
	}
	else {
		printf("Init failed: %d\n", init);
	}

	return 0;
}