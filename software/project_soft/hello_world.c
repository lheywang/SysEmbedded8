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

#include <stdio.h>
#include "alias.h"
#include "buzzer/buzzer.h"
#include "buzzer/note.h"
#include "hex/hex.h"
#include <sys/alt_irq.h>
#include <system.h>
#include <altera_avalon_pio_regs.h>
#include <unistd.h>

static void PWM_ISR(void *context, alt_u32 id)
{
	int button_position;
	button_position = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PWM_STATUS_BASE);
	IOWR_ALTERA_AVALON_PIO_DATA(PWM_STATUS_BASE, button_position);
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PWM_STATUS_BASE, 0x0);
    button_position = 0x0;

	printf("Interrupt from the PIO !");

	return;
}

static void SW_ISR(void *context, alt_u32 id)
{
	int button_position;
	button_position = IORD_ALTERA_AVALON_PIO_EDGE_CAP(BOUTONS_POUSSOIRS_BASE);
	IOWR_ALTERA_AVALON_PIO_DATA(BOUTONS_POUSSOIRS_BASE, button_position);
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BOUTONS_POUSSOIRS_BASE, 0x0);
    button_position = 0x0;

	printf("Interrupt from the PIO (SW) !");

	return;
}

int main()
{
  printf("Hello from Nios II!\n");

  // Enable interrupts
  printf("PIO NOK !\n");

  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PWM_STATUS_BASE, 0xFF);
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PWM_STATUS_BASE, 0x0);
  alt_ic_isr_register(PWM_STATUS_IRQ_INTERRUPT_CONTROLLER_ID, PWM_STATUS_BASE, (void *)PWM_ISR, NULL, 0x00);

  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BOUTONS_POUSSOIRS_BASE, 0xFF);
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BOUTONS_POUSSOIRS_BASE, 0x0);
  alt_ic_isr_register(BOUTONS_POUSSOIRS_IRQ_INTERRUPT_CONTROLLER_ID, BOUTONS_POUSSOIRS_BASE, (void *)SW_ISR, NULL, 0x00);

  // Play a note
  usleep(500 * 1000);
  buzzer_enable();
  buzzer_set_volume(255);
  buzzer_set_duration(100);
  buzzer_set_note(La4);
  buzzer_play();
  usleep(1200 * 1000);
  buzzer_play();

  // Hex displaying
  hex_display("cccccc", 6, 0);

  int cnt = 0;
  while(1){
	  usleep(1000 * 1000);
	  printf("Looping... %d\n", cnt++);
  }

  return 0;
}
