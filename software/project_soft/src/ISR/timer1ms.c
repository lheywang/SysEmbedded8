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
// ISR Helpers
#include "func/button_handler.h"
#include "func/led_blinker.h"
#include "func/song_select.h"
#include "func/hex_helper.h"

// Altera
#include <alt_types.h>

// STD
#include <stdio.h>

/** =======================================================================
 *	VARIABLES
 *  =======================================================================
 */
// Timestamp
static alt_u64 		Timestamp = 0;

// Variable to store the previous state of the buttons (edge detection)
static int 			MinuteButtonStatus = OFF;
static int 			HourButtonStatus = OFF;

// Variable to track the hex PWM
static alt_u64		HexDiff = 0;

// Alarm struct
static struct time 	Alarm = {	.hour = 0,
								.minute = 0,
								.second = 0};

// Song struct
static struct song 	*Song = &CrazyFrog;
static int			SongLaunched = 0;
static int 			MaintainRing = 0;

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

		// Identify for long presses (Only if the correct mode is selected, otherwise we save cycles)
		if ((SetHour == 1) | (SetAlarm == 1))
		{
			bp_IsButtonInLongPress(	0,
									MinButton,
									Timestamp,
									&MinuteButtonStatus);

			bp_IsButtonInLongPress(	1,
									HourButton,
									Timestamp,
									&HourButtonStatus);
		}

		// Change the correct time mode here
		if ((SetHour == 1) & (SetAlarm == 0))
		{
			bp_IncrementTimePerPress(	Ctx->Time,
										Timestamp,
										&MinuteButtonStatus,
										&HourButtonStatus);
		}
		else if ((SetHour == 0) & (SetAlarm == 1))
		{
			bp_IncrementTimePerPress(	&Alarm,
										Timestamp,
										&MinuteButtonStatus,
										&HourButtonStatus);
		}
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
		int ret = hexhelp_DefinePrintMessage(	buf,
									7,
									Timestamp,
									SetHour,
									SetAlarm,
									HourFormat,
									&Ctx->Time,
									&Alarm);

		hexhelp_Blink(buf, 6, 0, Timestamp, HexBrightness);

		/** =======================================================================
		 *	SONG UPDATE
		 *  =======================================================================
		 */

		Song = songSel_GetSong(SelectedMel, Song);

		/** =======================================================================
		 *	TIME COMPARISON
		 *  =======================================================================
		 */
		// This provide a latchup, than can only be set if the hour as overflowed
		// Thus, once the alarm has been disabled that's done for the day !
		// This does not affect the led blinking, which will remain on !
		Ctx->Ring = time_compare(Ctx->Time, &Alarm);
		if (Ctx->Ring < 0)
		{
			MaintainRing = 0;
		}

		/** =======================================================================
		 *	BUZZER PLAY
		 *  =======================================================================
		 */
		if ((Ctx->Ring == 1) & (AlarmEnabled == 1))
		{
			if ((SongLaunched == 0) & (MaintainRing == 0))
			{
				buzzer_play_song(Song);
				SongLaunched = 1;
				MaintainRing = 1;
			}
			ledblink_Blink(9, Timestamp, ALARM_BUZZ_HIGH, ALARM_BUZZ_PERIOD);
		}
		// If we shut down the switch, cut the song and the led !
		else
		{
			buzzer_stop_song();
			leds_SetLed(9, 0);
			SongLaunched = 0;
		}
	}
	ISR_LeaveMutex();

	return;
}
