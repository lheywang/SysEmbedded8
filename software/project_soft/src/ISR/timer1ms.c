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
#include "drivers/buzzer.h"
#include "ISR/ISR.h"
#include "func/button_handler.h"
#include "func/led_blinker.h"
#include "func/song_select.h"

// Altera
#include <alt_types.h>

// STD
#include <stdio.h>

/** =======================================================================
 *	VARIABLES
 *  =======================================================================
 */
// Timestamp
static alt_u64 Timestamp = 0;

// Variable to store the previous state of the buttons (edge detection)
static int MinuteButtonStatus = OFF;
static int HourButtonStatus = OFF;

// Variable to track the hex PWM
static alt_u64 HexTime = 0;

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */

void ISR_1MS(void *context)
{

	/** =======================================================================
	 *	DATA INPUT
	 *  =======================================================================
	 */

	// Clear the interrupt pin
	TIMER1MS_IOWR_STATUS(0x00);

	// User code
	// First, sample all user inputs :
	int buttons = BP_IORD_DATA;
	int switchs = SW_IORD_DATA;

	// Then, split the data into smaller variables, per function
	int AlarmEnabled = switchs & 0x00000001;
	int SetHour = (switchs & 0x00000002) >> 1;
	int SetAlarm = (switchs & 0x00000004) >> 2;
	int HourFormat = (switchs & 0x00000008) >> 3;
	int HexBrightness = (switchs & 0x00000070) >> 4;
	int SelectedMel = (switchs & 0x00000380) >> 7;

	int MinButton = (buttons & 0x01);
	int HourButton = (buttons & 0x02) >> 1;

	// Increment timestamp
	Timestamp += TIMER_PERIOD;

	/** =======================================================================
	 *	MAIN INTERRUPT CODE
	 *  =======================================================================
	 */

	int ret = ISR_GetMutex(0); // Don't wait. Update will be done next ms.
	if (ret == 0)
	{
		// Fetch and cast the context to our control struct
		struct ISR_Ctx *Ctx = (struct ISR_Ctx*)context;


		/** =======================================================================
		 *	ALARM LED STATUS
		 *  =======================================================================
		 */
		if (AlarmEnabled == 1)
		{
			ledblink_Blink(0, Timestamp, ALARM_HIGH, ALARM_PERIOD);
		}
		else
		{
			leds_SetLed(0, 0); // Ensure led is off.
		}

		/** =======================================================================
		 *	BUTTON HOUR INCREMENT
		 *  =======================================================================
		 */

		// Identify for long presses
		bp_IsButtonInLongPress(	0,
								MinButton,
								Timestamp,
								&MinuteButtonStatus);

		bp_IsButtonInLongPress(	1,
								HourButton,
								Timestamp,
								&HourButtonStatus);

		// Change the hour of the device
		if (SetHour == 1)
		{
			bp_IncrementTimePerPress(	Ctx->Time,
										Timestamp,
										&MinuteButtonStatus,
										&HourButtonStatus);
		}

		// Change the alarm hour
		else if (SetAlarm == 1)
		{
			bp_IncrementTimePerPress(	Ctx->Alarm,
										Timestamp,
										&MinuteButtonStatus,
										&HourButtonStatus);
		}

		// None, clear the values
		else
		{
			MinuteButtonStatus = OFF;
			HourButtonStatus = OFF;
		}

		/** =======================================================================
		 *	HOUR UPDATE STATUS
		 *  =======================================================================
		 */
		// Update hour on the 7 segments
		char buf[7] = {'\0'};
		if (HourFormat == 1) 			// 24 hour print
		{
			if (SetAlarm == 1)			// Alarm
			{
				time_print(Ctx->Alarm, buf);
			}
			else						// Else we show the time
			{
				time_print(Ctx->Time, buf);
			}

		}
		else							// 12 hour print
		{
			if (SetAlarm == 1)			// Alarm
			{
				time_print12(Ctx->Alarm, buf);
			}
			else						// Else we show the time
			{
				time_print12(Ctx->Time, buf);
			}
		}

		// 125 Hz PWM on the hex display, to enable some luminosity pulsations.
		alt_u64 HexInterval = Timestamp - HexTime;
		if (HexInterval <= (HexBrightness + 1)) // Ensure HEX is always ON !
		{
			// Enable hex
			hex_display(buf, 6, 0);
		}
		else if (HexInterval < 8)
		{
			// Disable hex
			hex_display("......", 6, 0);
		}
		else
		{
			// Clear timestamp
			HexTime = Timestamp;
		}

		/** =======================================================================
		 *	SONG UPDATE
		 *  =======================================================================
		 */

		Ctx->Song = songSel_GetSong(SelectedMel, Ctx->Song);

		/** =======================================================================
		 *	BUZZER PLAY
		 *  =======================================================================
		 */
		if ((Ctx->Ring == 1) & (AlarmEnabled == 1))
		{
			buzzer_play_song(Ctx->Song);
			ledblink_Blink(9, Timestamp, 500, 1000);
		}
		// If we shut down the switch, cut the song and the led !
		else
		{
			buzzer_stop_song();
			leds_SetLed(9, 0);
		}
	}
	ISR_LeaveMutex();

	return;
}
