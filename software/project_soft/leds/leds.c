/** =======================================================================
 * leds/leds.c
 *
 * Implement some functions to display on leds without headbanging on masks
 *
 * l.heywang
 * 10 / 04 / 2025
 *  =======================================================================
 */

/** =======================================================================
 *	LIBS
 *  =======================================================================
 */
// Header
#include "leds.h"

// Other headers
#include "../alias.h"

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */
int leds_SetLed(int led, int state)
{
	// Input checks
	if ((led < 0) | (led > 9))
	{
		return -1;
	}

	// Read actual IO port status
	int actual = LEDR_IORD_DATA;

	// Applying changes
	if (state) // led to be set
	{
		actual |= (1 << led);
	}
	else // led to be cleared
	{
		actual &= ~(1 << led);
	}

	// Perform IO
	LEDR_IOWR_DATA(actual);
	return 0;
}
