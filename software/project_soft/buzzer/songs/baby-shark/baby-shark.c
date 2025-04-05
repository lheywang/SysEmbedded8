/** =======================================================================
 * buzzer/songs/baby-shark/baby-shark.c
 *
 * Define values for the Baby Shark (Pinkfong) song.
 *
 * l.heywang
 * 05 / 03 / 2025
 *  =======================================================================
 */

#ifndef _DEF_BABY_SHARK
#define _DEF_BABY_SHARK

/** =======================================================================
 *	LIBS
 *  =======================================================================
 */
// Header
#include "baby-shark.h"

// Libs
#include "../../note.h"
#include "../songs.h"

/** =======================================================================
 *	DATA
 *  =======================================================================
 */

const int baby_shark_data[] = {
		// Line 1
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(30, DEFAULT_VOLUME, Fa3),
		_REG_FROM_PARAM(18, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(22, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(30, DEFAULT_VOLUME, Sol3),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, Do3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(30, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(18, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(22, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(30, DEFAULT_VOLUME, Si3_b),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, Fa3),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(24, DEFAULT_VOLUME, Do4),
		_REG_FROM_PARAM(17, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(21, DEFAULT_VOLUME, Do3),
		_REG_FROM_PARAM(17, DEFAULT_VOLUME, Do3),
		_REG_FROM_PARAM(21, DEFAULT_VOLUME, La2),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, Mi3),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(100, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, Re3),

		// EMpty space
		_REG_FROM_PARAM(25, MUTED, Re3),

		// Line 2
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(30, DEFAULT_VOLUME, Fa3),
		_REG_FROM_PARAM(18, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(22, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(30, DEFAULT_VOLUME, Sol3),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, Do3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(30, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(18, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(22, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(30, DEFAULT_VOLUME, Si3_b),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, Fa3),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(24, DEFAULT_VOLUME, Do4),
		_REG_FROM_PARAM(17, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(21, DEFAULT_VOLUME, Do3),
		_REG_FROM_PARAM(17, DEFAULT_VOLUME, Do3),
		_REG_FROM_PARAM(21, DEFAULT_VOLUME, La2),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, Mi3),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(100, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, Re3),
		_REG_FROM_PARAM(25, DEFAULT_VOLUME, Re3)
};

struct song BabySHark = {
	.name = "Baby-Shark",
	.artist = "Pinkfong",
	.len = sizeof(baby_shark_data),
	.notes = baby_shark_data
};

#endif /* _DEF_BABY_SHARK */
