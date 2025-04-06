/** =======================================================================
 * ISR/ISR.h
 *
 * Define the standard data types related to ISR and mutexes linked to
 * them
 *
 * l.heywang
 * 06 / 04 / 2025
 *  =======================================================================
 */

#ifndef _DEF_ISR
#define _DEF_ISR

/** =======================================================================
 *	LIBS
 *  =======================================================================
 */
#include "../time/ptime.h"
#include "../buzzer/buzzer.h"

/** =======================================================================
 *	STRUCTS
 *  =======================================================================
 */
struct ISR_Ctx {
	// Hour management
	struct time *Time;
	struct time *Alarm;

	// Song selection
	struct song *Song;

	// Board settings
	int Ring;
};

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */

/**
 * @brief 	This function request a mutex to access to the shared struct
 * 			to prevent any memory corruption.
 *
 * @param 	bool 	If set to >1, the function may block until the mutex
 * 					can be obtained.
 * 					Otherwise, return -1.
 *
 * @return 	int
 * @retval   0 		Mutex was obtained
 * @retval 	-1 		Mutex was not obtained. Memory corruption can occurs.
 */
int ISR_GetMutex(int wait);

/**
 * @brief 	This function leave the mutex to access the shared struct.
 *
 * @return 	int
 * @retval 	 0 		Mutex was released
 */
int ISR_LeaveMutex();

#endif /* _DEF_ISR */
