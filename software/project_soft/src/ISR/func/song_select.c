/** =======================================================================
 * ISR/func/song_select.c
 *
 * Implement a function to select the song we want based on some settings
 *
 * l.heywang
 * 12 / 04 / 2025
 *  =======================================================================
 */

/** =======================================================================
 * LIBS
 *  =======================================================================
 */
// Header
#include "song_select.h"

// Other headers
#include "drivers/buzzer.h"

/** =======================================================================
 * VARIABLES
 *  =======================================================================
 */
static int LastMel = 255;

/** =======================================================================
 * FUNCTIONS
 *  =======================================================================
 */
struct song* songSel_GetSong(int SelectedMel, struct song *Actual)
{
	if (LastMel != SelectedMel)
	{
		// Cancel the ongoing song
		buzzer_stop_song();

		// Select the new one.
		// Play will be triggered if needed.
		switch (SelectedMel)
		{
			case 0 :		// Elise
			{
#if (INCLUDE_ELISE == 1)
				return &Elise;
#endif
				break;
			}

			case 1 :		// Astronomia
			{
#if (INCLUDE_ASTRONOMIA == 1)
				return &Astronomia;
#endif
				break;
			}

			case 2 :		// Crazy frog
			{
#if (INCLUDE_CRAZY_FROG == 1)
				return &CrazyFrog;
#endif
				break;
			}

			case 3 :		// Baby Shark
			{
#if (INCLUDE_BABY_SHARK == 1)
				return &BabyShark;
#endif
				break;
			}

			case 4 :
			{
#if (0 == 1)
				// Unused for now
				return;
#endif
				break;
			}
			case 5 :
			{
#if (0 == 1)
				// Unused for now
				return;
#endif
				break;
			}

			case 6 :
			{
#if (0 == 1)
				// Unusued for now
				return;
#endif
				break;
			}

			case 7 :
			{
#if (0 == 1)
				// Unused for now
				return;
#endif
				break;
			}

			case 8 :
			{
#if (0 == 1)
				// Unused for now
				return;
#endif
				break;
			}

			default:
				return &Default;
				break;
		}

		LastMel = SelectedMel;
	}

	return Actual;
}
