/** =======================================================================
 * main.c
 *
 * Main source file of the project
 *
 * l.heywang
 * 06 / 04 / 2025
 *  =======================================================================
 */

/** =======================================================================
 *	LIBS
 *  =======================================================================
 */
// Headers
#include "init/init.h"
#include "ISR/ISR.h"

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */
int main()
{
	// Allocate and initialize a struct for the Interrupt Context
	struct ISR_Ctx Ctx;
	init_ISR_Ctx(&Ctx);

	// Init all peripherals
	init_PIO();

	// Init the different peripherals
	init_timer1s();
	init_timer1ms();
	init_pwm();

	/*
	 * After this point, all of the code executed is done under interrupts
	 */

	for (;;) {}

	return 0;
}
