/** =======================================================================
 * alias.h
 *
 * Define aliases to the ALTERA_AVALON Macros (because they're too long)
 *
 * l.heywang
 * 03 / 04 / 2025
 *  =======================================================================
 */

#ifndef _DEF_ALIAS
#define _DEF_ALIAS

/** =======================================================================
 *	LIBS
 *  =======================================================================
 */
// Altera headers
#include <system.h>
#include <altera_avalon_pio_regs.h>
#include <altera_avalon_timer_regs.h>

/** =======================================================================
 *	LEDS
 *  =======================================================================
 */
#define LEDR_IORD_DATA 				(IORD_ALTERA_AVALON_PIO_DATA(		LEDR_BASE							))
#define LEDR_IOWR_DATA(data) 		(IOWR_ALTERA_AVALON_PIO_DATA(		LEDR_BASE, 					data	))

/** =======================================================================
 *	SWITCHS
 *  =======================================================================
 */
#define SW_IORD_DATA 				(IORD_ALTERA_AVALON_PIO_DATA(		INTERRUPTEURS_BASE					))
#define SW_IOWR_DATA(data) 			(IOWR_ALTERA_AVALON_PIO_DATA(		INTERRUPTEURS_BASE, 		data	))

/** =======================================================================
 *	KEYS
 *  =======================================================================
 */
#define BP_IORD_DATA 				(IORD_ALTERA_AVALON_PIO_DATA(		BOUTONS_POUSSOIRS_BASE				))
#define BP_IOWR_DATA(data) 			(IOWR_ALTERA_AVALON_PIO_DATA(		BOUTONS_POUSSOIRS_BASE, 	data	))
#define BP_IORD_EDGE				(IORD_ALTERA_AVALON_PIO_EDGE_CAP(	BOUTONS_POUSSOIRS_BASE				))
#define BP_IOWR_EDGE(data)			(IOWR_ALTERA_AVALON_PIO_EDGE_CAP(	BOUTONS_POUSSOIRS_BASE, 	data	))
#define BP_IOWR_MASK(data) 			(IOWR_ALTERA_AVALON_PIO_IRQ_MASK(	BOUTONS_POUSSOIRS_BASE,		data	))

/** =======================================================================
 *	HEX
 *  =======================================================================
 */
#define HEX_IORD_DATA 				(IORD_ALTERA_AVALON_PIO_DATA(		HEX3_HEX0_BASE						))
#define HEX_IOWR_DATA(data) 		(IOWR_ALTERA_AVALON_PIO_DATA(		HEX3_HEX0_BASE, 			data	))
#define HEX2_IORD_DATA 				(IORD_ALTERA_AVALON_PIO_DATA(		HEX5_HEX4_BASE						))
#define HEX2_IOWR_DATA(data) 		(IOWR_ALTERA_AVALON_PIO_DATA(		HEX5_HEX4_BASE, 			data	))

/** =======================================================================
 *	BUZZER
 *  =======================================================================
 */
/*
 * Due to the architecture of the PWM peripheral (done by hand), there is one input and one output port.
 * To prevent any error within the NIOS II application, we perform each operation (Read or Write) to the
 * correct port, and does not declare operations that would create an error.
 */
#define PWM_IORD_DATA				(IORD_ALTERA_AVALON_PIO_DATA(		PWM_STATUS_BASE						))
#define PWM_IOWR_SDATA(data)		(IOWR_ALTERA_AVALON_PIO_DATA(		PWM_STATUS_BASE,			data	))
#define PWM_IOWR_DATA(data) 		(IOWR_ALTERA_AVALON_PIO_DATA(		PWM_CTRL_BASE, 				data	))
#define PWM_IORD_ODATA 				(IORD_ALTERA_AVALON_PIO_DATA(		PWM_CTRL_BASE						))
// Interrupts config for PWM
#define PWM_IORD_EDGE				(IORD_ALTERA_AVALON_PIO_EDGE_CAP(	PWM_STATUS_BASE						))
#define PWM_IOWR_EDGE(data)			(IOWR_ALTERA_AVALON_PIO_EDGE_CAP(	PWM_STATUS_BASE, 			data	))
#define PWM_IOWR_MASK(data)			(IOWR_ALTERA_AVALON_PIO_IRQ_MASK(	PWM_STATUS_BASE, 			data	))

/** =======================================================================
 *	TIMER 1S
 *  =======================================================================
 */
#define TIMER1S_IODR_CONTROL		(IORD_ALTERA_AVALON_TIMER_CONTROL(	SYS_SEC_BASE						))
#define TIMER1S_IOWR_CONTROL(data)	(IOWR_ALTERA_AVALON_TIMER_CONTROL(	SYS_SEC_BASE,				data	))
#define TIMER1S_IODR_STATUS			(IORD_ALTERA_AVALON_TIMER_STATUS(	SYS_SEC_BASE						))
#define TIMER1S_IOWR_STATUS(data)	(IOWR_ALTERA_AVALON_TIMER_STATUS(	SYS_SEC_BASE,				data	))

/** =======================================================================
 *	TIMER 1 ms
 *  =======================================================================
 */
#define TIMER1MS_IODR_CONTROL		(IORD_ALTERA_AVALON_TIMER_CONTROL(	SYS_CLK_TIMER_BASE					))
#define TIMER1MS_IOWR_CONTROL(data)	(IOWR_ALTERA_AVALON_TIMER_CONTROL(	SYS_CLK_TIMER_BASE,			data	))
#define TIMER1MS_IODR_STATUS		(IORD_ALTERA_AVALON_TIMER_STATUS(	SYS_CLK_TIMER_BASE					))
#define TIMER1MS_IOWR_STATUS(data)	(IOWR_ALTERA_AVALON_TIMER_STATUS(	SYS_CLK_TIMER_BASE,			data	))

#endif /* _DEF_ALIAS */
