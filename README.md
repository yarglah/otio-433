# otio
Library to control Otio 433 Mhz devices.

## Info
Otio is a french manifacturer of quite low cost 433 devices.
The library support 09HA01 and 09HA02 remote commands.
Model is indicated behind the device.

Library is based on RCSwicth.
OTIO commands are 32 bits length:
- 1 most significant byte: command identifier
- 3 less significant bytes: remote command device identifier

Command identifier change from device versions.
However a pattern is identified for the 2 supported devices:
Commands are the same between versions but with a 20 index shift (A01 A1_ON is A02 C3_ON)
Memory may be optimized by code if this assumption is confirmed on other models. 

## Receive and decode RC codes

Use OTIO_get_ID sample to retreive device ID, then OTIO_sample for test.
