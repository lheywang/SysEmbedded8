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
 *	LIBS
 *  =======================================================================
 */
#include "ISR/ISR.h"

/** =======================================================================
 *	FUNCTIONS (PERIPHERALS)
 *  =======================================================================
 */
/**
 * @brief 	Initialize all PIO peripherals on the NIOS II processor to an idle state
 *
 * @param 	None
 *
 * @return 	int
 * @retval 	 0 		Everything is fine !
 */
int init_PIO();

/**
 * @brief 	Initialize the ISR for the PWM engine. Does not start any song.
 *
 * @return 	int
 * @retval 	 0 			Struct was initialized
 * @retval 	-1 			Failed to initialize ISR
 */
int init_pwm();

/** =======================================================================
 *	FUNCTIONS (TIMERS)
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

/** =======================================================================
 *	FUNCTIONS (VARIABLE INIT)
 *  =======================================================================
 */
/**
 * @brief 	Initialize the ISR context struct, used to elegantly share data
 * 			between processes and ISR without needing global variables.
 *
 * @param 	ISR_Ctx 	A pointer to an ISR_Ctx context variable to be shared.
 *
 * @return 	int
 * @retval 	 0 			Struct was initialized
 * @retval 	-1 			Failed to initialize struct.
 */
int init_ISR_Ctx(struct ISR_Ctx *Ctx);

#endif /* _DEF_INIT */
