/** =======================================================================
 * ISR/ISR.c
 *
 * Implement the standard data types related to ISR and mutexes linked to
 * them
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
#include "ISR.h"

// Other headers
#include "../time/ptime.h"
#include "../buzzer/buzzer.h"

// STD
#include <unistd.h>

/** =======================================================================
 *	VARIABLE
 *  =======================================================================
 */
static int _Mutex = 0;

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */
int ISR_GetMutex(int wait)
{
	if (_Mutex == 0)
	{
		_Mutex = 1;
		return 0;
	}

	if (wait != 0)
	{
		// Wait until the mutex is acquired
		while (_Mutex == 1){usleep(1000);}
		_Mutex = 1;
		return 0;
	}

	return -1;
}

int ISR_LeaveMutex()
{
	_Mutex = 0;
	return 0;
}

