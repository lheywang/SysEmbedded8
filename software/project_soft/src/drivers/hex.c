/** =======================================================================
 * hex/hex.c
 *
 * Implement some functions about printing on the 7 segments
 *
 * l.heywang
 * 27 / 03 / 2025
 *  =======================================================================
 */

/** =======================================================================
 *	LIBS
 *  =======================================================================
 */
// Header
#include "drivers/hex.h"
#include "alias.h"

// STD
#include "stdint.h"
#include "stdio.h"

/** =======================================================================
 *	CHAR LUT
 *  =======================================================================
 */
//							binary val	   id char   7 - 6 - 5 - 4 - 3 - 2 - 1 - 0
static const int chars[] = {0b11000000, // 0    0            x   x   x   x   x   x
							0b11111001, //      1 						 x   x
							0b10100100, //  	2        x       x   x       x   x
							0b10110000, //  	3        x           x   x   x   x
							0b10011001, //  	4 		 x   x           x   x
							0b10010010, //  	5        x   x       x   x       x
							0b10000010, //  	6        x   x   x   x   x       x
							0b11111000, //  	7 						 x   x   x
							0b10000000, //  	8        x   x   x   x   x   x   x
							0b10010000, //  	9        x   x       x   x   x   x
							0b10001000, // 10	a        x   x   x       x   x   x
							0b10000011, //  	b        x   x   x   x   x
							0b11000110, //  	c 	         x   x   x           x
							0b10100001, //  	d        x       x   x   x   x
							0b10000110, //  	e        x   x   x   x           x
							0b10001110, //  	f        x   x   x               x
							0b10001001,	// 16 	h        x   x   x       x   x
							0b11101111, //  	i            x
							0b10100011, // 18 	o        x       x   x   x
							0b11100011, // 19 	u                x   x   x
							0b10111111, // 20	-        x
							0b11111111  // 21 	.    									!! Unwired on the board !!
};

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */

// Local function to convert from one base to the other !
int char27seg(char in, int * val)
{
	*val = 0; // Clear the value

	switch (in)
	{
	// Handling numbers
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		*val = chars[(in - 0x30) + 0];
		return 0;
		break;

	// Handling first letters
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		*val = chars[(in - 0x61) + 10];
		return 0;
		break;

	// Handling another group of letters
	case 'h':
	case 'i':
		*val = chars[(in - 0x68) + 16];
		return 0;
		break;

	// Last chars...
	case 'o':
		*val = chars[18];
		return 0;
		break;

	case 'u':
		*val = chars[19];
		return 0;
		break;

	// Handling two special chars
	case '-':
	case '.':
		*val = chars[(in - 0x2D) + 20];
		return 0;
		break;

	default:
		*val = 0b00000000; // ALL
		return -1;
	}

	return -1;
}

int hex_display(char* values, int len, int first)
{
	// First, ensure the operation is possible
	if ((first + len) > HEX_NB)
	{
		return -1;
	}
	if (len > HEX_NB)
	{
		return -1;
	}
	if ((first > HEX_NB - 1) | (first < 0))
	{
		return -1;
	}

	// Copy the data
	char buf[] = {'\0', '\0', '\0', '\0', '\0', '\0'};
	for (int k = first; k < first + len; k++)
	{
		buf[k] = values[k - first];
	}

	// Temp variables
	int tmp = 0;
	int err = 0;

	// 64 bits variable that represent the whole port
	uint64_t bits = 0;
	uint64_t mask = 0;
	uint64_t actual = ((uint64_t)HEX2_IORD_DATA << 32) | (uint64_t)HEX_IORD_DATA;

	for (int k = 0; k < HEX_NB; k++)
	{
		// Get the associated char (and return if a char is not handled !)
		if (char27seg(buf[k], &tmp) < 0)
		{
			err += 1;
		}

		// Clear the bits to write and write
		bits = bits << 8;
		mask = mask << 8;

		bits |= tmp;

		if (buf[k] == 0x00)
		{
			mask |= 0xFF;
		}
	}

	// Clearing the needed bits (mask contain 0 where char are)
	actual &= mask;

	// Inverting the mask and getting the masked bits (mask contain 1 where char are)
	mask = ~mask;
	bits &= mask;

	// Finally, getting the final bit stream
	bits = actual | bits;

	// Writing the new value
	HEX2_IOWR_DATA((bits & 0xFFFFFFFF00000000) >> 32); // HEX 5 and 4 (16 LSB are ignored)
	HEX_IOWR_DATA( bits & 0xFFFFFFFF); // HEX 3 to 0;

	return err;
}
