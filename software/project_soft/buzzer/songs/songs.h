/** =======================================================================
 * buzzer/songs/songs.h
 *
 * Define the interface to the songs functionnality, to play musics on the
 * buzzer.
 *
 * l.heywang
 * 05 / 04 / 2025
 *  =======================================================================
 */

#ifndef _DEF_SONGS
#define _DEF_SONGS

/** =======================================================================
 *	SONGS TO INCLUDE
 *  =======================================================================
 */
// Set to 0 to remove a song from the list
#define INCLUDE_CRAZY_FROG 		1
#define INCLUDE_ASTRONOMIA 		1
#define INCLUDE_BABY_SHARK 		1
#define INCLUDE_ELISE 			1

/** =======================================================================
 *	STRUCTS
 *  =======================================================================
 */
struct song {
	const char name[16];
	const char artist[16];
	const int len;
	const int *notes;
} defsong;

/** =======================================================================
 *	CONDITIONNAL INCLUDES
 *  =======================================================================
 */
#if (INCLUDE_CRAZY_FROG == 1)
#include "crazy-frog/crazy-frog.h"
#endif
// ------------------------------------------------------------------------
#if (INCLUDE_ASTRONOMIA == 1)
#include "astronomia/astronomia.h"
#endif
// ------------------------------------------------------------------------
#if (INCLUDE_BABY_SHARK == 1)
#include "baby-shark/baby-shark.h"
#endif
// ------------------------------------------------------------------------
#if (INCLUDE_ELISE == 1)
#include "elise/elise.h"
#endif
// ------------------------------------------------------------------------
#endif /* _DEF_SONGS */
