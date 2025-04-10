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
#include "alias.h"
#include "init/init.h"
#include "ISR/ISR.h"
#include "leds/leds.h"

#include <stdio.h>
#include <unistd.h>

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */
int main()
{
	// Initialize
	struct ISR_Ctx Ctx;
	init_ISR_Ctx(&Ctx);
	init_timer1s();

	for(int k = 0; k < 10; k ++)
	{
		leds_SetLed(k, 1);
		usleep(500 * 1000);
	}

	usleep(1000 * 1000);

	for(int k = 0; k < 10; k ++)
	{
		leds_SetLed(k, 0);
		usleep(500 * 1000);
	}

	/*
	 * After this point, all of the code executed is done under interrupts
	 */

	int cnt = 0;
	while(1)
	{
	  usleep(1000 * 1000);
	  printf("Looping... %d\n\r", cnt++);

	  printf("Buttons : %d; Edge %d\n\r", BP_IORD_DATA, BP_IORD_EDGE);
	  BP_IOWR_EDGE(BP_IORD_DATA);
	  printf("Status : %d; Edge %d\n\r", IORD_ALTERA_AVALON_PIO_DATA(PWM_STATUS_BASE), IORD_ALTERA_AVALON_PIO_EDGE_CAP(PWM_STATUS_BASE));
	  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PWM_STATUS_BASE,IORD_ALTERA_AVALON_PIO_DATA(PWM_STATUS_BASE));
	  printf("\n\n");
	}

  return 0;
}
