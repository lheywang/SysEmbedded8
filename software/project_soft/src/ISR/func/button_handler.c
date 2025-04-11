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

// Other headers
#include "structs/ptime.h"

// Altera
#include <alt_types.h>

// STD
#include <stddef.h>

/** =======================================================================
 * VARIABLES
 *  =======================================================================
 */
// BP Long/Short identification
static alt_u64  Stamps[BUTTON_NB] = {0};
static int 		Previous[BUTTON_NB] = {0};
static int 		LongRequired[BUTTON_NB] = {0};

// TimeIncrements
static alt_u64  LastStamp[2] = {0};
static int 		CNT[2] = {0};

/** =======================================================================
 * FUNCTIONS
 *  =======================================================================
 */

int bp_IsButtonInLongPress(int ButtonID, int Button, alt_u64 Timestamp, int *Status)
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
	if ((Button != Previous[ButtonID]) & (Button == 1))
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
	alt_u64 MinuteDelta = Timestamp - Stamps[ButtonID];

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

int bp_IncrementTimePerPress(struct time *Time, alt_u64 Timestamp, int *Status1, int *Status2)
{
	// Inputs checks
	if ((Time == NULL) | (Status1 == NULL) | (Status2 == NULL))
	{
		return -1;
	}

	int Error = 0;

	// Increment logic
	switch (*Status1) // BP 1
	{
		// Increment one single time, and reset the status
		case Short :
		{
			Error -= time_increment_custom(Time, BP1_STEP1);
			*Status1 = OFF;
			break;
		}

		// While status is long, increment every INCREMENT_STEP ms.
		// If the user maintain the press, the code will then accelerate the rate
		case Long :
		{
			alt_u64 MinuteTimestamp = Timestamp - LastStamp[0];
			if (MinuteTimestamp > INCREMENT_STEP)
			{
				if (CNT[0] < 10)
				{
					Error -= time_increment_custom(Time, BP1_STEP1);
				}
				else if (CNT[0] < 20)
				{
					Error -= time_increment_custom(Time, BP1_STEP2);
				}
				else
				{
					Error -= time_increment_custom(Time, BP1_STEP3);
				}
				CNT[0] += 1;
				LastStamp[0] = Timestamp;
			}
			break;
		}

		// Reset the counter to 0.
		case OFF:
		{
			CNT[0] = 0;
			break;
		}
	}

	switch (*Status2) // BP 2
	{
		// Increment one single time
		case Short :
		{
			Error -= time_increment_custom(Time, BP2_STEP1);
			*Status2 = OFF;
			break;
		}

		// As before, if the user maintain, increment gradually
		case Long :
		{
			alt_u64 HourTimestamp = Timestamp - LastStamp[1];
			if (HourTimestamp > INCREMENT_STEP)
			{
				if (CNT[1] < 10)
				{
					Error -= time_increment_custom(Time, BP2_STEP1);
				}
				else if (CNT[1] < 20)
				{
					Error -= time_increment_custom(Time, BP2_STEP2);
				}
				else
				{
					Error -= time_increment_custom(Time, BP2_STEP3);
				}
				CNT[1] += 1;
				LastStamp[1] = Timestamp;
			}
			break;
		}

		// Reset
		case OFF:
		{
			CNT[1] = 0;
			break;
		}
	}
	return Error;
}
