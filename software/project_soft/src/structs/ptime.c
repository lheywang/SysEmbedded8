/** =======================================================================
 * time/ptime.c
 *
 * Implement time management structs
 *
 * l.heywang
 * 03 / 04 / 2025
 *  =======================================================================
 */

/** =======================================================================
 *	LIBS
 *  =======================================================================
 */
// Header
#include "structs/ptime.h"

// STD
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */

int time_increment(struct time * const hour)
{
	// Input checks
	if (hour == NULL)
	{
		return -1;
	}

	// Increment seconds
	hour->second += 1;

	// Check if a minute is elapsed
	if (hour->second > 59)
	{
		hour->second = 0;
		hour->minute += 1;
	}

	// Check if an hour is elapsed
	if (hour->minute > 59)
	{
		hour->minute = 0;
		hour->hour += 1;
	}

	// Check if a day is elapsed (and output an overflow)
	if (hour->hour > 23)
	{
		hour->hour = 0;
		return -2;
	}

	return 0;
}

int time_print(const struct time * const hour, char buf[6])
{
	// Input checks
	if ((hour == NULL) | (buf == NULL))
	{
		return -1;
	}

	/*
	 * We print the value using sprintf, which return the number of char printed.
	 * We use that value to check for any formatting errors.
	 */

	strncpy(buf, (const char*)"......", 6);

	int val = 0;
	val = sprintf(&buf[0], "%02d", hour->hour);
	if (val > 2)
	{
		return -2;
	}
	val = sprintf(&buf[2], "%02d", hour->minute);
	if (val > 2)
	{
		return -2;
	}
	val = sprintf(&buf[4], "%02d", hour->second);
	if (val > 2)
	{
		return -2;
	}

	return 0;
}

int time_print12(const struct time * hour, char buf[6])
{
	// Input checks
	if ((hour == NULL) | (buf == NULL))
	{
		return -1;
	}

	// Create a new struct for temporary use
	struct time Ust = *hour;

	// Cast the 24:00 time to 12:00 time by using a modulo 12.
	// The only edge case is 0:00 or 12:00 which is addressed by the if.
	Ust.hour = hour->hour % 12;
	if ((hour->hour == 12) | (hour->hour == 0))
	{
		Ust.hour = 12;
	}

	// Call the default function, to not duplicate code...
	time_print(&Ust, buf);

	return 0;
}

int time_compare(const struct time * A, const struct time * B)
{
	// Inputs checks
	if ((A == NULL) | (B == NULL))
	{
		return -128;
	}

	// First, check for the hour and return if we can direct match
	if (A->hour > B->hour)
	{
		return 1;
	}
	else if (A->hour < B->hour)
	{
		return -1;
	}

	// In case of equality, check for the minutes
	if (A->minute > B->minute)
	{
		return 1;
	}
	else if (A->minute < B->minute)
	{
		return -1;
	}

	// In case of equality, check for the seconds
	if (A->second > B->second)
	{
		return 1;
	}
	else if (A->second < B->second)
	{
		return -1;
	}

	// That's a perfect match, return 0.
	return 0;
}
