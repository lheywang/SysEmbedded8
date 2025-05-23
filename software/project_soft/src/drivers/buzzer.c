/** =======================================================================
 * buzzer/buzzer.c
 *
 * Implement some functions about the buzzer management (proper peripheral)
 *
 * l.heywang
 * 04 / 03 / 2025
 *  =======================================================================
 */

/** =======================================================================
 *	LIBS
 *  =======================================================================
 */

// Headers
#include "drivers/buzzer.h"
#include "../buzzer/note.h"

#include "alias.h"

// STD
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

// Altera
#include <sys/alt_irq.h>

/** =======================================================================
 *	FILES VARIABLES
 *  =======================================================================
 */
// Theses are used by the musical engine to track the different notes to be
// played/
static int *data = NULL;
static int len = 0;
static int actual = 0;
static int pad_required = 0;

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */

/**
 * Index of functions
 * 	- Global management of the buzzer : 	l.57
 * 	- Note management						l.84
 * 	- Launching of notes					l.145
 * 	- Song interface 						l.166
 * 	- ISR 									l.215
 */

/*
 * BUZZER MANAGEMENT
 */
int buzzer_enable()
{
	// Set the bit 31 to 0 to enable
	uint32_t tmp_reg = PWM_IORD_ODATA;
	tmp_reg &= 0x7FFFFFFF;
	PWM_IOWR_DATA(tmp_reg);

	return 0;
}

int buzzer_disable()
{
	// Set the bit 31 to 1 to disable
	uint32_t tmp_reg = PWM_IORD_ODATA;
	tmp_reg |= 0x80000000;
	PWM_IOWR_DATA(tmp_reg);

	return 0;
}

/*
 * NOTES MANAGEMENT
 */
int buzzer_set_note(enum note freq)
{
	// Set the 8 LSB
	uint32_t tmp_reg = PWM_IORD_ODATA;
	uint8_t tmp_val = freq & 0xFF;

	// Bit masking to configure the 8 LSBS.
	tmp_reg &= 0xFFFFFF00;
	tmp_reg |= tmp_val;

	// Write
	PWM_IOWR_DATA(tmp_reg);

	return 0;
}

int buzzer_set_volume(int volume)
{
	// Inputs checks
	if ((volume > 255) | (volume < 0))
	{
		return -1;
	}

	// Set the 15-8 LSB
	uint32_t tmp_reg = PWM_IORD_ODATA;
	uint8_t tmp_val = volume & 0xFF;

	// Bit masking to configure the 15-8 LSBS.
	tmp_reg &= 0xFFFF00FF;
	tmp_reg |= (tmp_val << 8);

	// Write
	PWM_IOWR_DATA(tmp_reg);

	return 0;
}

int buzzer_set_duration(int ms)
{
	// Inputs checks
	if ((ms > 255) | (ms < 0))
	{
		return -1;
	}

	// Set the 23-16 LSB
	uint32_t tmp_reg = PWM_IORD_ODATA;
	uint8_t tmp_val = ms & 0xFF;

	// Bit masking to configure the 23-16 LSBS.
	tmp_reg &= 0xFF00FFFF;
	tmp_reg |= (tmp_val << 16);

	// Write
	PWM_IOWR_DATA(tmp_reg);

	return 0;
}

/*
 * BUZZER TRIGGERS EVENTS
 */
int buzzer_play()
{
	// Set the bit 30 to 1 to trigger start.
	uint32_t tmp_reg = PWM_IORD_ODATA;
	tmp_reg |= 0x40000000;
	PWM_IOWR_DATA(tmp_reg);

	usleep(1); // 1 microsecond to let the hardware register the event.

	// Set back the bit 30 to 0 to re-arm the device
	tmp_reg &= 0xBFFFFFFF;
	PWM_IOWR_DATA(tmp_reg);

	return 0;
}


/*
 * BUZZER SONG INTERFACE
 */
int buzzer_play_song(const struct song *Song)
{
	if (Song == NULL)
	{
		return -1;
	}

	// Copy the data to our local expression.
	data = (int *)Song->notes;
	len = (int)Song->len - 1;
	actual = 0;

	// Initialize the buzzer
	buzzer_enable();

  	// Start the play of the first note
  	int reg = data[actual];
	buzzer_set_duration((reg & 0x00FF0000) >> 16);
	buzzer_set_volume((reg & 0x0000FF00) >> 8);
	buzzer_set_note((reg & 0x000000FF));
	actual += 1;
	buzzer_play();

	// Exit.
	return 0;
}

/*
 * ISR
 */
void _SONG_ISR(void *context)
{
	// Handle the interrupt source
    PWM_IOWR_SDATA(PWM_IORD_EDGE);
    PWM_IOWR_EDGE(0x00);

    // Check if we're at the end
    if (actual == len)
    {
    	// Return
    	return;
    }

	// One note over two, we insert a small delay between them.
	// This make the listening for fluent.
	// This is done by requesting a note for a duration INTERVAL
	// at volume 0;
	if (pad_required == 1)
	{
		buzzer_set_duration(INTERVAL);
		buzzer_set_volume(0);
		pad_required = 0;
	}
	else
	{
		int reg = data[actual];
		buzzer_set_duration((reg & 0x00FF0000) >> 16);
		buzzer_set_volume((reg & 0x0000FF00) >> 8);
		buzzer_set_note((reg & 0x000000FF));
		actual += 1;
		pad_required = 1;
	}

	// Play
	buzzer_play();

	return;
}
