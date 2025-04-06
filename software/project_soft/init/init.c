/** =======================================================================
 * init/init.c
 *
 * Implement standard peripherals initialization and so...
 *
 * l.heywang
 * 06 / 04 / 2025
 *  =======================================================================
 */

/** =======================================================================
 *	LIBS
 *  =======================================================================
 */
// Header
#include "init.h"

// Other headers
#include "../alias.h"
#include "../ISR/timer1ms/timer1ms.h"
#include "../ISR/timer1s/timer1s.h"
#include "../ISR/ISR.h"

// Altera
#include <altera_avalon_timer_regs.h>
#include <sys/alt_irq.h>

// STD
#include <stddef.h>

/** =======================================================================
 *	VARIABLES
 *  =======================================================================
 */
static struct ISR_Ctx *ISR_Data;

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */

int init_timer1s()
{
	// Register the interrupt
	int res = alt_ic_isr_register(	SYS_SEC_IRQ_INTERRUPT_CONTROLLER_ID,
							SYS_SEC_IRQ,
							(void*)ISR_1S,
							(void*)ISR_Data,
							0x0);
	if (res != 0)
	{
		return -1;
	}


	// Init the timer
	TIMER1S_IOWR_CONTROL(	ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
							ALTERA_AVALON_TIMER_CONTROL_START_MSK |
							ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);

	return 0;
}

int init_timer1ms()
{
	// Register the interrupt
	int res = alt_ic_isr_register(	SYS_CLK_TIMER_IRQ_INTERRUPT_CONTROLLER_ID,
									SYS_CLK_TIMER_IRQ,
									(void*)ISR_1MS,
									(void*)ISR_Data,
									0x0);
	if (res != 0)
	{
		return -1;
	}


	// Init the timer
	TIMER1MS_IOWR_CONTROL(	ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
							ALTERA_AVALON_TIMER_CONTROL_START_MSK |
							ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);

	return 0;
}

int init_ISR_Ctx(struct ISR_Ctx *Ctx)
{
	// Input checks
	if (Ctx == NULL)
	{
		return -1;
	}

	// Initialize alarm time
	Ctx->Alarm->hour = 0;
	Ctx->Alarm->minute = 0;
	Ctx->Alarm->second = 0;

	// Initialize actual time
	Ctx->Time->hour = 0;
	Ctx->Time->minute = 0;
	Ctx->Time->second = 0;

	// Initialize song
	Ctx->Song = &CrazyFrog;

	// Initialize status
	Ctx->Ring = 0;

	// Define the variable used in our file as the one passed
	ISR_Data = Ctx;

	return 0;
}

