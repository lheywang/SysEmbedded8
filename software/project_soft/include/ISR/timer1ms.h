/** =======================================================================
 * ISR/timer1ms/timer1ms.h
 *
 * Define the standard ISR for the timer on 1ms
 *
 * l.heywang
 * 06 / 04 / 2025
 *  =======================================================================
 */

#ifndef _DEF_ISR_1MS
#define _DEF_ISR_1MS

/** =======================================================================
 *	DEFINED PARAMETERS
 *  =======================================================================
 */
// GENERIC SETTINGS
#define TIMER_PERIOD 1; // 1 ms

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */

/**
 * ISR for the 1 second timer
 */
void ISR_1MS(void *context);

#endif /* _DEF_ISR_1MS */
