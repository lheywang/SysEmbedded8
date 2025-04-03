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
#include "ptime.h"

// STD
#include <stddef.h>
#include <stdio.h>

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */

int time_increment(struct time * const hour){
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

int time_print(const struct time * const hour, char buf[6]){
	// Input checks
	if (hour == NULL)
	{
		return -1;
	}

	/*
	 * We print the value using sprintf, which return the number of char printed.
	 * We use that value to check for any formatting errors.
	 */

	buf = "......"; // empty char (. is not handled by the hex.h lib).

	int val = 0;
	val = sprintf(&buf[0], "%d", hour->hour);
	if (val > 2)
	{
		return -2;
	}
	val = sprintf(&buf[2], "%d", hour->minute);
	if (val > 2)
	{
		return -2;
	}
	val = sprintf(&buf[4], "%d", hour->second);
	if (val > 2)
	{
		return -2;
	}

	return 0;
}
