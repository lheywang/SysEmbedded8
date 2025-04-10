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
#include "ISR/timer1ms.h"

// Other headers
#include "alias.h"
#include "drivers/leds.h"
#include "drivers/hex.h"
#include "ISR/ISR.h"
#include "func/button_handler.h"

// STD
#include <stdint.h>
#include <stdio.h>

/** =======================================================================
 *	VARIABLES
 *  =======================================================================
 */
// Timestamp
static uint64_t Timestamp = 0;

// Variable for different subprocess timed by timestamp
static uint64_t LedTime = 0;

// Variable to store the previous state of the buttons (edge detection)
static int MinuteButtonStatus = OFF;
static int HourButtonStatus = OFF;

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

	int MinButton = (buttons & 0x01);
	int HourButton = (buttons & 0x02) >> 1;

	// Increment timestamp
	Timestamp += TIMER_PERIOD;

	int ret = ISR_GetMutex(0); // Don't wait. Update will be done next ms.
	if (ret == 0)
	{
		// Fetch and cast the context to our control struct
		struct ISR_Ctx *Ctx = (struct ISR_Ctx*)context;


		/** =======================================================================
		 *	ALARM LED STATUS
		 *  =======================================================================
		 */
		uint64_t LedInterval = Timestamp - LedTime;
		if (AlarmEnabled == 1)
		{
			if (LedInterval <= ALARM_HIGH)
			{
				// Enable led
				leds_SetLed(0, 1);
			}
			else if (LedInterval < (ALARM_HIGH + ALARM_PERIOD))
			{
				leds_SetLed(0, 0);
			}
			else
			{
				LedTime = Timestamp;
			}
		}
		else
		{
			leds_SetLed(0, 0); // Ensure led is off.
		}

		/** =======================================================================
		 *	LONG PRESS DETECTION
		 *  =======================================================================
		 */

		bp_IsButtonInLongPress(0, MinButton, Timestamp, &MinuteButtonStatus);
		bp_IsButtonInLongPress(1, HourButton, Timestamp, &HourButtonStatus);

		/** =======================================================================
		 *	TEST DISPLAY
		 *  =======================================================================
		 */
		switch (MinuteButtonStatus) {
		case OFF :
			leds_SetLed(8, 0);
			leds_SetLed(9, 0);
			break;

		case Long :
			leds_SetLed(8, 0);
			leds_SetLed(9, 1);
			// MinuteButtonStatus = OFF;
			break;

		case Short :
			leds_SetLed(8, 1);
			leds_SetLed(9, 0);
			// MinuteButtonStatus = OFF;
			break;
		}

		switch (HourButtonStatus) {
		case OFF :
			leds_SetLed(6, 0);
			leds_SetLed(7, 0);
			break;

		case Long :
			leds_SetLed(6, 0);
			leds_SetLed(7, 1);
			// MinuteButtonStatus = OFF;
			break;

		case Short :
			leds_SetLed(6, 1);
			leds_SetLed(7, 0);
			// MinuteButtonStatus = OFF;
			break;
		}

		/** =======================================================================
		 *	HOUR UPDATE STATUS
		 *  =======================================================================
		 */
		// Update hour on the 7 segments
		char buf[7] = {'\0'};
		if (HourFormat == 1)
		{
			time_print(Ctx->Time, buf); 	// 24 hour print
			// Add some leds here ?
		}
		else
		{
			time_print12(Ctx->Time, buf);	// 12 hour print
			// Add some leds here ?
		}

		hex_display(buf, 6, 0);

		/** =======================================================================
		 *	BUZZER PLAY
		 *  =======================================================================
		 */
		// buzzer_play_song(Ctx->Song);
	}
	ISR_LeaveMutex();

	return;
}
