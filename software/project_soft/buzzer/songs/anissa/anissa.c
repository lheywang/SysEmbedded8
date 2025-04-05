/** =======================================================================
 * buzzer/songs/anissa.c
 *
 * Define values for the Anissa (Wejdene) song.
 *
 * l.heywang
 * 05 / 03 / 2025
 *  =======================================================================
 */

/** =======================================================================
 *	LIBS
 *  =======================================================================
 */
// Header
#include "anissa.h"

// Libs
#include "../../note.h"
#include "../songs.h"

/** =======================================================================
 *	DATA
 *  =======================================================================
 */

const int anissa_data[] = {
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

const struct song Anissa = {
	.name = "Anissa",
	.artist = "Wejdene",
	.len = sizeof(anissa_data),
	.notes = anissa_data
};
