/** =======================================================================
 * buzzer/buzzer.h
 *
 * Define some functions about the buzzer management (proper peripheral)
 *
 * This header expose two main interfaces :
 * 	- A note oriented one, for "low level" interractions
 * 	- A song oriented one, build arround the songs/songs.h file, that
 * 		define more advanced functionnalities.
 *
 * l.heywang
 * 04 / 03 / 2025
 *  =======================================================================
 */

#ifndef _DEF_BUZZER
#define _DEF_BUZZER

/** =======================================================================
 *	LIBS
 *  =======================================================================
 */
// Sublibs
#include "../../src/buzzer/note.h"
#include "../../src/buzzer/songs.h"

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */

/**
 * @brief 	Set the played note on the buzzer
 *
 * @param 	freq	A member of the "note" enum
 *
 * @return	int
 * @retval 	 0 		Everything went fine
 */
int buzzer_set_note(enum note freq);

/**
 * @brief 	Set the play volume of the buzzer
 *
 * @warning	The buzzer is linear, so the volumes are.
 * 			+10 in the volume may thus not produce the same gain
 *
 * @param 	volume 	An integer between 0 and 255 that represent the volume
 *
 * @return 	int
 * @retval 	 0 		Everything went fine
 * @retval 	-1 		Invalid volume
 */
int buzzer_set_volume(int volume);

/**
 * @brief 	Set the future note duration
 *
 * @param 	int 	The number of 10 milliseconds packet where the note shall be played
 * 					1 = 10 ms
 * 					2 = 20 ms
 * 					...
 * 					255 = 2550 ms
 *
 * @return 	int
 * @retval 	 0 		Operation went fine
 * @retval 	-1 		Value too long. Int shall be between 0 and 10 ms
 */
int buzzer_set_duration(int ms);

/**
 * @brief 	Enable and disable respectively the PWM
 *
 * @return 	1
 */
int buzzer_enable();
int buzzer_disable();

/**
 * @brief 	Play the configured tone
 *
 * @return	1
 */
int buzzer_play();

/**
 *	@brief 		Register the play of the song (or cancel it)
 *
 *	@warning	This function make the usage of interruptions for each note.
 *				This may overhide previously defined settings.
 *
 *	@param 		struct song		A pointer to a song struct to be played
 *
 *	@return 	int
 *	@return 	 0 				Everything went fine
 *	@return 	-1 				Invaling pointer
 *	@return 	-2 				Could not register the interrupts
 *	@return 	-3 				Song already in play.
 */
int buzzer_play_song(const struct song *Song);
int buzzer_stop_song();

#endif /* _DEF_BUZZER */
