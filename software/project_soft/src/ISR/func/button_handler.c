/** =======================================================================
 * ISR/func/button_handler.c
 *
 * Implement the standard data types related to ISR and mutexes linked to
 * them
 *
 * l.heywang
 * 10 / 04 / 2025
 *  =======================================================================
 */

/** =======================================================================
 * LIBS
 *  =======================================================================
 */
// Header
#include "button_handler.h"

// STD
#include <stdint.h>
#include <stddef.h>

/** =======================================================================
 * VARIABLES
 *  =======================================================================
 */
static uint64_t Stamps[BUTTON_NB] = {0};
static int 		Previous[BUTTON_NB] = {0};
static int 		LongRequired[BUTTON_NB] = {0};

/** =======================================================================
 * FUNCTIONS
 *  =======================================================================
 */

int bp_IsButtonInLongPress(int ButtonID, int Button, uint64_t Timestamp, int *Status)
{
	// Inputs checks
	if ((0 > ButtonID) | (ButtonID > 2))
	{
		return -1;
	}
	if (Status == NULL)
	{
		return -2;
	}

	// Start a counter if the value seen on the button is different that the one registered
	if ((Button != Previous[ButtonID]) & Button == 1)
	{
		Previous[ButtonID] = Button;
		Stamps[ButtonID] = Timestamp;
		LongRequired[ButtonID] = 1;
	}

	if (Button == 0)
	{
		Previous[ButtonID] = 0;

		// Clear the status only if Long status.
		// This produce a latching short output to not miss one, while ensuring the long will be gone once the button is released.
		if (*Status == Long)
		{
			*Status = OFF;
		}
	}

	// Get the timestamp, to ensure we don't go too fast !
	uint64_t MinuteDelta = Timestamp - Stamps[ButtonID];

	if ((MinuteDelta > TLONG) && (LongRequired[ButtonID] == 1))
	{
		// Soft lock to prevent looking too many times
		LongRequired[ButtonID] = 0;

		// Set the button variable as needed.
		if (Button == 1)
		{
			*Status = Long;
		}
		else
		{
			*Status = Short;
		}
	}
	return 0;
}
