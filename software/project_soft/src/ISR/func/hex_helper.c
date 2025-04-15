/** =======================================================================
 * ISR/func/hex_helper.c
 *
 * Implement a some functions to make the hex blink or select the correct
 * value for enough time
 *
 * l.heywang
 * 13 / 04 / 2025
 *  =======================================================================
 */

/** =======================================================================
 * LIBS
 *  =======================================================================
 */
// Header
#include "hex_helper.h"

// Other headers
#include "drivers/hex.h"

// Altera
#include <alt_types.h>

// STD
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/** =======================================================================
 * FILE VARIABLES
 *  =======================================================================
 */
// Brightness controller
static alt_u64 HexTime = 0;
static alt_u64 HexLast = 0;

// CMD restore
static int LastCmd = 255;

// Buffer storage
static char saveBuf[7] = {0};

/** =======================================================================
 * FUNCTIONS
 *  =======================================================================
 */
int hexhelp_DefinePrintMessage(	char *buf,
								int len,
								alt_u64 Timestamp,
								int ShowHour,
								int ShowAlarm,
								int HourFormat,
								struct time *Time,
								struct time *Alarm)
{
	// Input checks
	if ((buf == NULL) | (Time == NULL) | (Alarm == NULL))
	{
		return -1;
	}
	if (len < 7)
	{
		return -2;
	}

	// Then, compute a single mask to group all values into a single switch case
	int cmd = 	((HourFormat == 0) ? 0 : 1) << 2 |
				((ShowAlarm == 0) ? 0 : 1) << 1 |
				((ShowHour == 0) ? 0 : 1);

	// Then, we have 8 cases to cover all the options
	/*
	 *   	Format		ShowHour	ShowAlarm		Action
	 *   	0			0			0				--> Show actual time as 24 hour format
	 *   	0			0			1				--> Show alarm as 24 hour format
	 *   	0			1			0				--> Show actual time as 24 hour format
	 *   	0			1			1				--> No prints. Return error immediately.
	 *
	 *   	1			0			0				--> Show actual time as 12 hour format
	 *   	1			0			1				--> Show alarm as 12 hour format
	 *   	1			1			0				--> Show actual time as 12 hour format
	 *   	1			1			1				--> No prints. Return error immediately.
	 *
	 * And, in any cases : If the format has changed, we show for HEX_MAINTAIN ms some infos on it,
	 * such as " 12 H  " or equivalent.
	 */

	switch (cmd)
	{
		// 24h prints
		case 0b001 :
		{
			time_print(Alarm, buf);
			break;
		}
		case 0b000 :
		case 0b010 :

		{
			time_print(Time, buf);
			break;
		}

		// 12h prints
		case 0b101 :
		{
			time_print12(Alarm, buf);
			break;
		}
		case 0b100 :
		case 0b110 :
		{
			time_print12(Time, buf);
			break;
		}
		case 0b011 :
		case 0b111 :
		{
			char *newval = "..err.";
			strncpy(buf, newval, 6);
			return -3;
		}
	}

	// Then, add a bit of logic to show the user the mode has changed.
	// We display some indications for HEX_MAINTAIN ms.

	if (cmd != LastCmd)
	{
		// First, get the different bits XOR
		int diff = cmd ^ LastCmd;
		LastCmd = cmd;
		HexLast = Timestamp;

		if (diff & 0b100) // Handle time format change
		{
			char *newval = (cmd & 0b100) ? ".12.h.." : ".24.h..";
			strncpy(saveBuf, newval, 6);
		}
		else if (diff & 0b010) // Handle alarm showing
		{
			char *newval = (cmd & 0b010) ? ".hour" : ".hour";
			strncpy(saveBuf, newval, 6);
		}
		else if (diff & 0b001) // Handle alarm showing
		{
			char *newval = (cmd & 0b001) ? ".alarm" : ".hour.";
			strncpy(saveBuf, newval, 6);
		}

	}

	if ((HexLast + HEX_MAINTAIN) > Timestamp) 	// An info display was required so we copy the data.
												// Otherwise, the buffer was already formatted.
	{
		strncpy(buf, saveBuf, 6);				// Copy the char from one buf to the other
	}

	return 0;
}

int hexhelp_Blink(char *buf, int len, int pos, alt_u64 Timestamp, int Brightness)
{
	// Input checks
	if (buf == NULL)
	{
		return -1;
	}

	// 67.5 Hz PWM on the hex display, to enable some luminosity pulsations.
	alt_u64 HexInterval = Timestamp - HexTime;
	if (HexInterval <= (Brightness + 1) << 1)
	{
		// Enable hex
		hex_display(buf, len, pos);

	}
	else if (HexInterval < 16)
	{
		// Disable hex
		hex_display("......", 6, 0);
	}
	else
	{
		// Clear timestamp
		HexTime = Timestamp;
	}

	return 0;
}
