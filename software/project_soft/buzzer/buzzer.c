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
	if ((volume > 255) | (volume < 0))
	{
		return -1;
	}

	// Set the 16-8 LSB
	uint32_t tmp_reg = PWM_IORD_ODATA;
	uint8_t tmp_val = volume & 0xFF;

	// Bit masking to configure the 16-8 LSBS.
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
