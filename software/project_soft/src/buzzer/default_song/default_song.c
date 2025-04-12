/** =======================================================================
 * buzzer/default_song/default_song.c
 *
 * Define values for the default song
 *
 * l.heywang
 * 05 / 04 / 2025
 *  =======================================================================
 */

/** =======================================================================
 *	LIBS
 *  =======================================================================
 */
// Header
#include "default_song.h"

// Libs
#include "../note.h"
#include "../songs.h"

/** =======================================================================
 *	DATA
 *  =======================================================================
 */

int default_data[] = {
		// Line 1
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
		_REG_FROM_PARAM(50, DEFAULT_VOLUME, La3),
		_REG_FROM_PARAM(50, MUTED, La3),
};

struct song Default = {
	.name = "Default",
	.artist = "?",
	.len = (sizeof(default_data) / sizeof(int)),
	.notes = default_data
};
