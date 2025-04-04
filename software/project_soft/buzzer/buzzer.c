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
#include "buzzer.h"
#include "note.h"

#include "../alias.h"

// STD
#include <stdint.h>
#include <unistd.h>

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
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

int buzzer_play_song(const struct song *Song)
{
	if (Song == NULL)
	{
		return -1;
	}

	// Do something here

	return 0;
}
