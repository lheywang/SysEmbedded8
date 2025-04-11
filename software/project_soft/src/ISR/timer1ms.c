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

// Last mel, to not cut music when we start a another one
static int LastMel = 0;

// Variable to track led blinking
static alt_u64 LedTime = 0;

// Variable to track the hex PWM
static alt_u64 HexTime = 0;

// Variable to track the led PWM on the ALARM led
static alt_u64 LedAlarmTime = 0;

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
	int AlarmACK = (switchs & 0x00000008) >> 3;
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
		if (AlarmEnabled == 1)
		{
			alt_u64 LedInterval = Timestamp - LedTime;

			// Evaluate sections
			if (LedInterval <= ALARM_HIGH)
			{
				// Enable led
				leds_SetLed(0, 1);
			}
			else if (LedInterval < (ALARM_HIGH + ALARM_PERIOD))
			{
				// Disable led
				leds_SetLed(0, 0);
			}
			else
			{
				// Clear timestamp
				LedTime = Timestamp;
			}
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

		if (ShowHour == 1) 	// Change the hour of the device
		{
			leds_SetLed(7, 1);
			leds_SetLed(6, 0);
			bp_IncrementTimePerPress(	Ctx->Time,
										Timestamp,
										&MinuteButtonStatus,
										&HourButtonStatus);
		}

		else				// Change the alarm hour
		{
			leds_SetLed(7, 0);
			leds_SetLed(6, 1);
			bp_IncrementTimePerPress(	Ctx->Alarm,
										Timestamp,
										&MinuteButtonStatus,
										&HourButtonStatus);
		}

		/** =======================================================================
		 *	HOUR UPDATE STATUS
		 *  =======================================================================
		 */
		// Update hour on the 7 segments
		char buf[7] = {'\0'};
		if (HourFormat == 1) 			// 24 hour print
		{
			if (ShowHour == 1)			// Time
			{
				time_print(Ctx->Time, buf);
			}
			else						// Alarm
			{
				time_print(Ctx->Alarm, buf);
			}

		}
		else							// 12 hour print
		{
			if (ShowHour == 1)			// Time
			{
				time_print12(Ctx->Time, buf);
			}
			else						// Alarm
			{
				time_print12(Ctx->Alarm, buf);
			}
		}

		// 125 Hz PWM on the hex display, to enable some luminosity pulsations.
		alt_u64 HexInterval = Timestamp - HexTime;
		if (HexInterval <= HexBrightness)
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

		if (LastMel != SelectedMel)
		{
			// Cancel the ongoing song
			buzzer_stop_song();

			// Select the new one.
			// Play will be triggered if needed.
			switch (SelectedMel)
			{
				case 0 :		// Elise
				{
#if (INCLUDE_ELISE == 1)
					Ctx->Song = &Elise;
#endif
					break;
				}

				case 1 :		// Astronomia
				{
#if (INCLUDE_ASTRONOMIA == 1)
					// Ctx->Song = &Astronomia;
#endif
					break;
				}

				case 2 :		// Crazy frog
				{
#if (INCLUDE_CRAZY_FROG == 1)
					Ctx->Song = &CrazyFrog;
#endif
					break;
				}

				case 3 :		// Baby Shark
				{
#if (INCLUDE_BABY_SHARK == 1)
					// Ctx->Song = &BabyShark;
#endif
					break;
				}

				case 4 :
				{
#if (0 == 1)
					// Unused for now
#endif
					break;
				}
				case 5 :
				{
#if (0 == 1)
					// Unused for now
#endif
					break;
				}

				case 6 :
				{
#if (0 == 1)
					// Unusued for now
#endif
					break;
				}

				case 7 :
				{
#if (0 == 1)
					// Unused for now
#endif
					break;
				}

				case 8 :
				{
#if (0 == 1)
					// Unused for now
#endif
					break;
				}

				default:
					break;
			}

			LastMel = SelectedMel;
		}

		/** =======================================================================
		 *	BUZZER PLAY
		 *  =======================================================================
		 */
		if (Ctx->Ring == 1)
		{
			buzzer_play_song(Ctx->Song);

			// Blink a led when the alarm is ringing !
			alt_u64 LedAlarmInterval = Timestamp - LedAlarmTime;
			if (LedAlarmInterval <= 500)
			{
				// Enable led
				leds_SetLed(9, 1);
			}
			else if (LedAlarmInterval < 1000)
			{
				// Disable led
				leds_SetLed(9, 0);
			}
			else
			{
				// Clear timestamp
				LedTime = Timestamp;
			}

			// If button is pressed, audio is cutted but led remain on !
			if (AlarmACK == 1)
			{
				buzzer_stop_song();
			}
		}
	}
	ISR_LeaveMutex();

	return;
}
