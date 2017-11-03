
#include <OTIO.h>

OTIO_COMMAND stringToCommand(String command)
{
	if (command == "A1_ON")		return A1_ON;
	if (command == "A1_OFF")	return A1_OFF;
	if (command == "A2_ON")		return A2_ON;
	if (command == "A2_OFF")	return A2_OFF;
	if (command == "A3_ON")		return A3_ON;
	if (command == "A3_OFF")	return A3_OFF;
	if (command == "A4_ON")		return A4_ON;
	if (command == "A4_OFF")	return A4_OFF;
	
	if (command == "B1_ON")		return B1_ON;
	if (command == "B1_OFF")	return B1_OFF;
	if (command == "B2_ON")		return B2_ON;
	if (command == "B2_OFF")	return B2_OFF;
	if (command == "B3_ON")		return B3_ON;
	if (command == "B3_OFF")	return B3_OFF;
	if (command == "B4_ON")		return B4_ON;
	if (command == "B4_OFF")	return B4_OFF;

	if (command == "C1_ON")		return C1_ON;
	if (command == "C1_OFF")	return C1_OFF;
	if (command == "C2_ON")		return C2_ON;
	if (command == "C2_OFF")	return C2_OFF;
	if (command == "C3_ON")		return C3_ON;
	if (command == "C3_OFF")	return C3_OFF;
	if (command == "C4_ON")		return C4_ON;
	if (command == "C4_OFF")	return C4_OFF;

	if (command == "D1_ON")		return D1_ON;
	if (command == "D1_OFF")	return D1_OFF;
	if (command == "D2_ON")		return D2_ON;
	if (command == "D2_OFF")	return D2_OFF;
	if (command == "D3_ON")		return D3_ON;
	if (command == "D3_OFF")	return D3_OFF;
	if (command == "D4_ON")		return D4_ON;
	if (command == "D4_OFF")	return D4_OFF;

	return UNKNOWN;
}

String commandToString(OTIO_COMMAND command) 
{
	switch (command)
	{
		case A1_ON: 	return "A1_ON";
		case A1_OFF: 	return "A1_OFF";
		case A2_ON: 	return "A2_ON";
		case A2_OFF: 	return "A2_OFF";
		case A3_ON: 	return "A3_ON";
		case A3_OFF: 	return "A3_OFF";
		case A4_ON: 	return "A4_ON";
		case A4_OFF: 	return "A4_OFF";
		
		case B1_ON: 	return "B1_ON";
		case B1_OFF: 	return "B1_OFF";
		case B2_ON: 	return "B2_ON";
		case B2_OFF: 	return "B2_OFF";
		case B3_ON: 	return "B3_ON";
		case B3_OFF: 	return "B3_OFF";
		case B4_ON: 	return "B4_ON";
		case B4_OFF: 	return "B4_OFF";

		case C1_ON: 	return "C1_ON";
		case C1_OFF: 	return "C1_OFF";
		case C2_ON: 	return "C2_ON";
		case C2_OFF: 	return "C2_OFF";
		case C3_ON: 	return "C3_ON";
		case C3_OFF: 	return "C3_OFF";
		case C4_ON: 	return "C4_ON";
		case C4_OFF: 	return "C4_OFF";

		case D1_ON: 	return "D1_ON";
		case D1_OFF: 	return "D1_OFF";
		case D2_ON: 	return "D2_ON";
		case D2_OFF: 	return "D2_OFF";
		case D3_ON: 	return "D3_ON";
		case D3_OFF: 	return "D3_OFF";
		case D4_ON: 	return "D4_ON";
		case D4_OFF: 	return "D4_OFF";

		default: return "UNKNOWN";
	}
}
