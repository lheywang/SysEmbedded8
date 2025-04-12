/** =======================================================================
 * ISR/func/song_select.h
 *
 * Define a function to select the song we want based on some settings
 *
 * l.heywang
 * 12 / 04 / 2025
 *  =======================================================================
 */

#ifndef _DEF_SONG_SELECT
#define _DEF_SONG_SELECT

/** =======================================================================
 * LIBS
 *  =======================================================================
 */
#include "drivers/buzzer.h"

/** =======================================================================
 * FUNCTIONS
 *  =======================================================================
 */

/**
 * @brief 	Return a pointer to the associated song structure.
 *
 * @warning	If a song was currently played, this function will stop it !
 *
 * @param 	SelectedMel	Selected song (0 to 7)
 *
 * @return song*		A pointer to the song structure.
 */
struct song* songSel_GetSong(int SelectedMel, struct song* Actual);


#endif /* _DEF_LED_BLINKER */
