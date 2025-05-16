/** =======================================================================
 * ISR/func/led_blinker.c
 *
 * Implement a led blinker function to make a led blink at any rate wanted
 *
 * l.heywang
 * 12 / 04 / 2025
 *  =======================================================================
 */

/** =======================================================================
 * LIBS
 *  =======================================================================
 */
// Header
#include "led_blinker.h"

// Other headers
#include "drivers/leds.h"

// Altera
#include <alt_types.h>

/** =======================================================================
 * FILE VARIABLES
 *  =======================================================================
 */
static alt_u64 LedTime[NB_LEDS] = {0};

/** =======================================================================
 * FUNCTIONS
 *  =======================================================================
 */
int ledblink_Blink(	int led,
					alt_u64 Timestamp,
					int HIGH,
					int PERIOD)
{
	// Input checks
	if ((led < 0) | (led > 9))
	{
		return -1;
	}

	// Get interval
	alt_u64 LedInterval = Timestamp - LedTime[led];

	// Evaluate sections
	if (LedInterval <= HIGH)
	{
		// Enable led
		leds_SetLed(led, 1);
	}
	else if (LedInterval < (HIGH + PERIOD))
	{
		// Disable led
		leds_SetLed(led, 0);
	}
	else
	{
		// Clear timestamp
		LedTime[led] = Timestamp;
	}

	return 0;
}
