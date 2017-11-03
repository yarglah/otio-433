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

#include <OTIO.h>
#include <OTIO_helper.h>

#define RC_1 0xC3B300
#define RC_2 0xCC0100

#define RC_PIN_SEND	2
#define RC_PIN_RECV	9

unsigned long devices[] = {RC_1, RC_2};

OTIO otio = OTIO(OTIO_09HA02, devices, 2, RC_PIN_SEND, RC_PIN_RECV);

void setup() {
  Serial.begin(9600);
  otio.send(A2_OFF);
  otio.send(A2_ON);
}

void loop() {
  OTIO_COMMAND action = otio.recv();

  if (action != UNKNOWN) {
    Serial.println(commandToString(action));
    Serial.flush();
	otio.send(action);
  }

  // send data only when you receive data:
  if (Serial.available() > 0) {
          // read the incoming byte:
          String commandString = Serial.readStringUntil('\r');
          Serial.flush();
          commandString.trim();
          OTIO_COMMAND action = stringToCommand(commandString);
          if (action != UNKNOWN) {
            otio.send(action);
            Serial.println(commandToString(action));
            Serial.flush();
          }
  }

}
