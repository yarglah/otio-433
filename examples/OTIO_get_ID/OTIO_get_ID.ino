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

// Initialize with no device ID
OTIO otio = OTIO(OTIO_09HA02, 0, 10, 2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long deviceID = otio.getID();

  if (deviceID != 0) {
    Serial.print("Device ID: Ox");
    Serial.println(deviceID, HEX);
  }
}
