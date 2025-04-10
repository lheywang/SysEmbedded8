/** =======================================================================
 * ISR/timer1ms/timer1ms.c
 *
 * Implement the standard ISR for the timer on 1ms
 *
 * l.heywang
 * 06 / 04 / 2025
 *  =======================================================================
 */

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */
// Header
#include "timer1ms.h"

// Other headers
#include "../../alias.h"

// STD
#include <stdint.h>

/** =======================================================================
 *	VARIABLES
 *  =======================================================================
 */
// Timestamp
static uint64_t Timestamp = 0;

// Variable for different subprocess timed by timestamp
static uint64_t LedTime = 0;

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */

void ISR_1MS(void *context)
{
	// Clear the interrupt pin
	TIMER1MS_IOWR_STATUS(0x00);

	// User code
	// First, sample all user inputs :
	int buttons = BP_IORD_DATA;
	int switchs = SW_IORD_DATA;

	// Then, split the data into smaller variables, per function
	int AlarmEnabled = switchs & 0x00000001;
	int ShowHour = (switchs & 0x00000002) >> 1;
	int HourFormat = (switchs & 0x00000004) >> 2;
	int HexBrightness = (switchs & 0x00000070) >> 4;
	int SelectedMel = (switchs & 0x00000380) >> 7;

	// Increment timestamp
	Timestamp += TIMER_PERIOD;

	// ALARM Led handler
	uint64_t LedInterval = Timestamp - LedTime;
	if (LedInterval <= ALARM_HIGH)
	{
		// Enable led
		__asm("nop");
	}
	else if (LedInterval < (ALARM_HIGH + ALARM_PERIOD))
	{
		__asm("nop");
	}
	else
	{
		LedTime = Timestamp;
	}

	return;
}
