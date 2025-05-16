/** =======================================================================
 * ISR/func/button_handler.h
 *
 * Define a button handler to identify if the button is only pressed,
 * or pressed a long time.
 * Also define the associated actions to be performed.
 *
 * l.heywang
 * 10 / 04 / 2025
 *  =======================================================================
 */

#ifndef _DEF_BP_HANDLER
#define _DEF_BP_HANDLER

/** =======================================================================
 * LIBS
 *  =======================================================================
 */
// Other headers
#include "structs/ptime.h"

// Altera
#include <alt_types.h>

/** =======================================================================
 *	DEFINES
 *  =======================================================================
 */
// Threshold duration, in ms
#define TLONG 200 // 200 ms

// Increment steps
#define INCREMENT_STEP 200
// BP1
#define BP1_STEP1 1			// 1 second for the first step
#define BP1_STEP2 10		// 10 seconds for the second step
#define BP1_STEP3 60		// 60 seconds for the third step
// BP2
#define BP2_STEP1 (1 * 60)	// 1 minute increment for the first step
#define BP2_STEP2 (10 * 60) // 10 minutes increment for the second step
#define BP2_STEP3 (60 * 60) // 1 hour increment for the third step

// Buttons number
#define BUTTON_NB 2

/** =======================================================================
 *	ENUMS
 *  =======================================================================
 */
enum Press{
	OFF,
	Short,
	Long,
};

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */

/**
 * @brief 	Identify if the button is pressed short (< TLONG ms), or long press (> TLONG ms)
 *
 * @warning	Short(enum) state must be cleared by hand, the long one is cleared by the function.
 * 			This ensure you can't miss a short press.
 *
 * @param 	ButtonId : 	ID of the button. Needed to generalize on a single function.
 * @param 	Button : 	Actual value of the button
 * @param 	Timestamp : 64 bit value of the actual timestamp. If not incremented every 1 ms, TLONG shall be adapted.
 * @param 	*Status : 	Status of the value. Take a member of the enum Press value.
 *
 * @return 	int
 * @retval 	 0 			Computation went fine ! Value may be actualized
 * @retval 	-1 			Invalid ButtonID
 * @retval 	-2 			NULL pointer for Status.
 */
int bp_IsButtonInLongPress(int ButtonID, int Button, alt_u64 Timestamp, int *Status);

/**
 * @brief 	Increment the time actually shown by a defined amount @ref define section.
 *
 * @param 	Time 		A time struct pointer to be incremented.
 * @param 	Timestamp	System timestamp.
 * @param 	Status1		The actual status of the button1
 * @param 	Status2 	The actual status of the button2
 *
 * @return 	int
 * @retval 	 0 		Computation went fine
 * @retval 	-1		Invalid pointers passed
 * @retval  -2		Hour overflow.
 */
int bp_IncrementTimePerPress(struct time *Time, alt_u64 Timestamp, int *Status1, int *Status2);


#endif /* _DEF_BP_HANDLER */
