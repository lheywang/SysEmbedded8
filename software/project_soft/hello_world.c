/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include "alias.h"
#include "buzzer/buzzer.h"
#include "hex/hex.h"
#include "time/ptime.h"

#include <stdio.h>
#include <sys/alt_irq.h>
#include <system.h>
#include <altera_avalon_pio_regs.h>
#include <unistd.h>

static void SW_ISR(void *context)
{
	int button_position;
	button_position = IORD_ALTERA_AVALON_PIO_EDGE_CAP(BOUTONS_POUSSOIRS_BASE);
	IOWR_ALTERA_AVALON_PIO_DATA(BOUTONS_POUSSOIRS_BASE, button_position);
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BOUTONS_POUSSOIRS_BASE, button_position);
	return;
}

int main()
{
  printf("Hello from Nios II!\n\n\r");

  BP_IOWR_MASK(0x3);
  BP_IOWR_DATA(0x00);
  BP_IOWR_EDGE(0x00);
  alt_ic_isr_register(BOUTONS_POUSSOIRS_IRQ_INTERRUPT_CONTROLLER_ID, BOUTONS_POUSSOIRS_IRQ, (void *)SW_ISR, NULL, 0x00);


  // Launch a music
  // buzzer_play_song(&Astronomia);

  struct time Act = {.hour = 10,
		  	  	  	  .minute = 49,
					  .second = 59
  };
  time_increment(&Act);
  time_increment(&Act);



  // Hex displaying
  char buf[7] = {'\0'};
  printf("print = %d\n", time_print(&Act, buf));
  printf("Printed hour %6s\n", buf);
  hex_display(buf, 6, 0);

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
