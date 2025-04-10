/** =======================================================================
 * ISR/func/button_handler.h
 *
 * Define a button handler to identify if the button is only pressed, or pressed a long time
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
// STD
#include <stdint.h>

/** =======================================================================
 *	DEFINES
 *  =======================================================================
 */
// Threshold duration, in ms
#define TLONG 200 // 200 ms

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
int bp_IsButtonInLongPress(int ButtonID, int Button, uint64_t Timestamp, int *Status);


#endif /* _DEF_BP_HANDLER */
