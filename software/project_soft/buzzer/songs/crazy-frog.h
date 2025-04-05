/** =======================================================================
 * buzzer/songs/crazy-frog.h
 *
 * Define values for the crazy frog song.
 *
 * l.heywang
 * 04 / 03 / 2025
 *  =======================================================================
 */

#ifndef _DEF_CRAZY_FROG
#define _DEF_CRAZY_FROG

/** =======================================================================
 *	LIBS
 *  =======================================================================
 */
// Headers
#include "songs.h"

/** =======================================================================
 *	DATA
 *  =======================================================================
 */

#if (INCLUDE_CRAZY_FROG == 1)
int crazy_frog_data[] = {
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

struct song CrazyFrog = {
	.name = "Crazy-Frog",
	.len = sizeof(crazy_frog_data),
	.notes = crazy_frog_data
};

#endif /* INCLUDE_CRAZY_FROG */
#endif /* _DEF_CRAZY_FROG */
