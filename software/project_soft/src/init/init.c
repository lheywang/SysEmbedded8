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
#include "init/init.h"

// Other headers
#include "alias.h"
#include "ISR/timer1ms.h"
#include "ISR/timer1s.h"
#include "ISR/ISR.h"
#include "drivers/buzzer.h"

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

int init_pwm()
{
	// Register the interrupt
  	int ret = alt_ic_isr_register(	PWM_STATUS_IRQ_INTERRUPT_CONTROLLER_ID,
  									PWM_STATUS_IRQ,
									(void *)_SONG_ISR,
									NULL,
									0x00);

  	if (ret != 0)
  	{
  		return -1;
  	}


	// Initialize the interrupts for the PWM to see
	PWM_IOWR_MASK(0x40); // --> Only the END NOTE FLAG
	PWM_IOWR_EDGE(0x00);
	PWM_IOWR_SDATA(0x00);

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

	// Initialize actual time
	Ctx->Time->hour = 0;
	Ctx->Time->minute = 0;
	Ctx->Time->second = 0;

	// Initialize status
	Ctx->Ring = 0;

	// Define the variable used in our file as the one passed
	ISR_Data = Ctx;

	return 0;
}

int init_PIO()
{
	// Initialize LEDS to OFF
	LEDR_IOWR_DATA(0x00000000);

	// Initialize Buttons to the default state
	BP_IOWR_DATA(0x00000000);
	BP_IOWR_EDGE(0x00000000);
	BP_IOWR_MASK(0x00000000);

	// Initialize the 7-segment display (common cathode, so inverted logic)
	HEX_IOWR_DATA(0xFFFFFFFF);
	HEX2_IOWR_DATA(0xFFFFFFFF);

	// Initialize PWM peripheral
	PWM_IOWR_SDATA(0x00000000);
	PWM_IOWR_EDGE(0x00000000);
	PWM_IOWR_DATA(0x00000000);
	PWM_IOWR_MASK(0x00000000);

	return 0;
}

