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

#define TELID 0xC3B300
#define PIN_LED 13

OTIO otio = OTIO(OTIO_09HA02, TELID, 10, 2);

void setup() {
  Serial.begin(9600);

  Serial.println("Setup: A2_OFF");
  otio.send(A2_OFF);

  digitalWrite(PIN_LED, LOW);
}

void loop() {
  OTIO_COMMAND action = otio.recv();

  if (action != UNKNOWN) {
    digitalWrite(PIN_LED, HIGH);

    Serial.print("Received: ");
    Serial.println(action, HEX);
    if (action == A2_OFF) {
          otio.send(A2_ON);
          Serial.println("Fiat lux !");
    }
    digitalWrite(PIN_LED, LOW);
  }

  // send data only when you receive data:
  if (Serial.available() > 0) {
          // read the incoming byte:
          int incomingByte = Serial.read();

          switch (incomingByte) {
                  break;
            case '2': otio.send(A2_OFF);
              break;
            case 10:
            case 13:
              break;
           default:
/*
              Serial.print("Serial in: ");
              Serial.println(incomingByte, DEC);
              */
              break;
          }
  }

}
