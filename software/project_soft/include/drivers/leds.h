/** =======================================================================
 * leds/leds.h
 *
 * Define some functions to display on leds without headbanging on masks
 *
 * l.heywang
 * 10 / 04 / 2025
 *  =======================================================================
 */

#ifndef _DEF_LEDS
#define _DEF_LEDS

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */

/**
 * @brief 	Set a led state, without modifying others
 *
 * @param 	led		Integer to define the led, from 0 to 9
 * @param 	state 	Integer to define the state. If != 0, led is ON.
 *
 * @return 	int
 * @retval 	 0 		Operation sucessfull
 * @retval 	-1 		Invalid led value
 */
int leds_SetLed(int led, int state);


#endif /* _DEF_LEDS */
