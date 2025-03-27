/** =======================================================================
 * HEX.c
 *
 * Define some functions about printing on the 7 segments
 *
 * l.heywang
 * 27 / 03 / 2025
 *  =======================================================================
 */

// Multiple include guard
#ifndef _DEF_HEX
#define _DEF_HEX

/** =======================================================================
 *	DEFINES
 *  =======================================================================
 */

#define HEX_NB	4

/** =======================================================================
 *	LIBS
 *  =======================================================================
 */

// Local libs
#include "../alias.h"

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */

/**
 *	@brief Print an array of (len) char to the 7 segments.
 *
 *	@warning 	Not all char are possible. Only numbers + '-', a, b, c, d, e, f, g, h, i, o, p, q, u are supported
 *
 *	@param values 		char to be printed.
 *	@param len 			number of char to be printed
 *	@param first		the first display to be modified
 *
 *	@return int
 *	@retval  0 	operation sucessfull
 *	@retval -1 	invalid len (too long ?)
 *	@retval -2 	invalid char
 */
int hex_display(char* values, int len, int first);


#endif

