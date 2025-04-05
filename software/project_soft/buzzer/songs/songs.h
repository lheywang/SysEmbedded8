/** =======================================================================
 * buzzer/songs/songs.h
 *
 * Define the interface to the songs functionnality, to play musics on the
 * buzzer.
 *
 * l.heywang
 * 04 / 04 / 2025
 *  =======================================================================
 */

#ifndef _DEF_SONGS
#define _DEF_SONGS

/** =======================================================================
 *	LIBS
 *  =======================================================================
 */
// Headers
#include "../note.h"

/** =======================================================================
 *	SONGS TO INCLUDE
 *  =======================================================================
 */
// Set to 0 to remove a song from the list
#define INCLUDE_CRAZY_FROG 1
#define INCLUDE_ASTRONOMIA 1
#define INCLUDE_HAPPY_BIRTHDAY 1
#define INCLUDE_BABY_SHARK 1
#define INCLUDE_ELISE 1
#define INCLUDE_ANISSA 1

/** =======================================================================
 *	SONGS PARAMETERS
 *  =======================================================================
 */
#define DEFAULT_VOLUME 8

// Sub defines
#define SMALL_VOLUME 	((DEFAULT_VOLUME / 4) * 2)
#define MEDIUM_VOLUME 	((DEFAULT_VOLUME / 4) * 3)
#define MEDIUM_VOLUME 	((DEFAULT_VOLUME / 4) * 3)

/** =======================================================================
 *	SONGS BUILDING DEFINE (Enable data compression on the memory).
 *  =======================================================================
 */

#define _REG_FROM_PARAM(duration, volume, note) \
	((duration & 0xFF) << 16) | ((volume & 0xFF) << 8) | (note & 0xFF)

/** =======================================================================
 *	STRUCTS
 *  =======================================================================
 */
typedef struct song {
	char name[16];
	int len;
	int *notes;
};
#endif /* _DEF_SONGS */
