/** =======================================================================
 * time/ptime.h
 *
 * Define time management structs and functions
 *
 * l.heywang
 * 03 / 04 / 2025
 *  =======================================================================
 */

#ifndef _DEF_TIME
#define _DEF_TIME

/** =======================================================================
 *	STRUCTS
 *  =======================================================================
 */
struct time {
	int hour;
	int minute;
	int second;
};

/** =======================================================================
 *	FUNCTIONS
 *  =======================================================================
 */

/**
 *	@brief	Increment the hour pointed by the time struct by one second
 *			Handle every hour / minute and so incrementation.
 *
 *	@param	hour 	A pointer to a time struct to be incremented.
 *
 *	@return int
 *	@retval  0 		Everything went fine
 *	@retval -1 		Invalid pointer
 *	@retval -2 		Overflow detected
 */
int time_increment(struct time * const hour);

/**
 * @brief 	Return the formatted text output on 6 char [hhmmss] (24h or 12h for the __12 function)
 *
 * @param 	hour 	A pointer to a time struct to be printed
 * @param 	buf 	A pointer to a 6 char array.
 *
 * @return int
 * @return  0 		Everything went fine
 * @return -1 		Invalud pointer
 * @return -2 		Failed to format the output
 */
int time_print(const struct time * hour, char buf[6]);
int time_print12(const struct time * hour, char buf[6]);

/**
 * @brief 	Compare two hours
 *
 * @param 	hour	A pointer to a time struct A
 * @param 	hour 	A pointer to a time struct B
 *
 * @return 	int
 * @return 	0		Times are equal
 * @return 	>1 		Time A is greater than time B
 * @return <1(>-127)Time A is smaller than time B
 * @return -128 	Invalid pointers provided
 */
int time_compare(const struct time * A, const struct time * B);


#endif /* _DEF_TIME */
