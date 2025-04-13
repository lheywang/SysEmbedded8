/** =======================================================================
 * ISR/func/led_blinker.h
 *
 * Define a led blinker function to make a led blink at any rate wanted
 *
 * l.heywang
 * 12 / 04 / 2025
 *  =======================================================================
 */

#ifndef _DEF_LED_BLINKER
#define _DEF_LED_BLINKER


// Altera
#include <alt_types.h>

/** =======================================================================
 * DEFINES
 *  =======================================================================
 */
// ALARM LED BLINK PERIOD
#define ALARM_HIGH 500
#define ALARM_PERIOD 4500
#define ALARM_BUZZ_HIGH 250
#define ALARM_BUZZ_PERIOD 250

/** =======================================================================
 * FUNCTIONS
 *  =======================================================================
 */
/**
 *	@brief 	Command a led to make it blink accordingly to some settings
 *			passed.
 *
 *	@param 	led 		The led to be controlled, from 0 to 9
 *	@param 	Timestamp	The system timestamp
 *	@param 	HIGH 		HIGH period length, in Timestamp unit steps
 *	@param 	PERIOD		Total period length for the blink
 *
 *	@return int
 *	@retval	 0 			Operation done sucessfully
 *	@retval -1			Invalid led
 *	@retval -2 			Failed to control the led
 */
int ledblink_Blink(	int led,
					alt_u64 Timestamp,
					int HIGH,
					int PERIOD);

#endif /* _DEF_LED_BLINKER */
