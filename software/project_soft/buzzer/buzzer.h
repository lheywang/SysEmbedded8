/** =======================================================================
 * buzzer/buzzer.h
 *
 * Define some functions about the buzzer management (proper peripheral)
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
#include "note.h"

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
 * @brief 	Enable and disable respectively the PWM
 *
 * @return 	1
 */
int buzzer_enable();
int buzzer_disable();

#endif /* _DEF_BUZZER */
