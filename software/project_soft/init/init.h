/** =======================================================================
 * init/init.h
 *
 * Define standard peripherals initialization and so...
 *
 * l.heywang
 * 06 / 04 / 2025
 *  =======================================================================
 */

#ifndef _DEF_INIT
#define _DEF_INIT

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */
/**
 * @brief 	Initialize the 1 second timer, and bind the interrupt to it.
 *
 * @param 	None
 *
 * @return 	 0 		Initialization went fine
 * @return 	-1 		Failed to initialize the interrupt routine
 */
int init_timer1s();

/**
 * @brief 	Initialize the 1 millisecond timer, and bind the interrupt to it.
 *
 * @param 	None
 *
 * @return 	 0 		Initialization went fine
 * @return 	-1 		Failed to initialize the interrupt routine
 */
int init_timer1ms();

#endif /* _DEF_INIT */
