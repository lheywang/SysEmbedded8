/** =======================================================================
 * ISR/timer1s/timer1s.c
 *
 * Implement the standard ISR for the timer on 1ms
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
#include "timer1s.h"

// Other headers
#include "../ISR.h"
#include "../../alias.h"
#include "../../time/ptime.h"
#include "../../hex/hex.h"

// STD
#include <stdio.h>

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */

void ISR_1S(void *context)
{
	// Clear the interrupt pin
	TIMER1S_IOWR_STATUS(0x00);

	// User code
	int ret = ISR_GetMutex(1); // Wait for ever until we get the mutex. The other thread exit every 1 ms, so worst case is 1 ms.
	if (ret == 0)
	{
		// Fetch and cast the context to our control struct
		struct ISR_Ctx *Ctx = (struct ISR_Ctx*)context;

		// Increment the time counter and if needed, trigger the alarm (-> Will be played in a another interrupt)
		time_increment(Ctx->Time);
		if (time_compare(Ctx->Time, Ctx->Alarm) > 0)
		{
			Ctx->Ring = 1;
		}
	}

	// Free the mutex we got on the mutex.
	ISR_LeaveMutex();

	// Increment the time
	return;
}
