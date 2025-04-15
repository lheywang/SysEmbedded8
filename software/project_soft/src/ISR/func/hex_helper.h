/** =======================================================================
 * ISR/func/hex_helper.h
 *
 * Define a some functions to make the hex blink or select the correct
 * value for enough time
 *
 * l.heywang
 * 13 / 04 / 2025
 *  =======================================================================
 */

#ifndef _DEF_HEX_HELPER
#define _DEF_HEX_HELPER

/** =======================================================================
 * LIBS
 *  =======================================================================
 */
// Other headers
#include "structs/ptime.h"

// Altera
#include <alt_types.h>

/** =======================================================================
 *	DEFINES
 *  =======================================================================
 */
// HEX MAINTAIN INFO TIME
#define HEX_MAINTAIN 2000

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */

/**
 * @brief 	Fill the buffer with the correct message for our needs !
 *
 * @param 	*buf 		The buffer to be filled
 * @param 	len 		The length of the buffer (> 6 or error !)
 * @param 	Timestamp	The system timestamp
 * @param 	ShowHour 	The bit for the hour display
 * @param 	ShowAlarm	The bit for the alarm display
 * @param 	HourFormat	The bit for the 12:00 or 24:00 display
 * @param 	*Time		The actual time struct
 * @param 	*Alarm 		The actual Alarm struct
 *
 * @return 	int
 * @retval 	 0 			Operation successfull
 * @retval 	-1 			Invalid pointers (buf or Time or Alarm)
 * @retval 	-2 			Buffer too small
 * @retval 	-3 			Invalid combination of ShowAlarm and ShowHour.
 */
int hexhelp_DefinePrintMessage(	char *buf,
								int len,
								alt_u64 Timestamp,
								int ShowHour,
								int ShowAlarm,
								int HourFormat,
								struct time *Time,
								struct time *Alarm);

/**
 * @brief 	Command the blinking of the HEX display to ensure different luminosity levels
 *
 * @param 	buf 		The buffer to be displayed
 * @param 	len			The length of the buffer
 * @param 	pos			The position where the buffer is placed on the hex
 * @param 	Timestamp	The system timestamp
 * @param 	Brightness 	The wanted brightness
 *
 * @return 	int
 * @retval 	 0 			Operation successfull
 * @retval 	-1 			Invalid pointer
 */
int hexhelp_Blink(char *buf, int len, int pos, alt_u64 Timestamp, int Brightness);

#endif /* _DEF_HEX_HELPER */
