/** =======================================================================
 * buzzer/note.h
 *
 * Define the notes values and volumes
 *
 * l.heywang
 * 04 / 03 / 2025
 *  =======================================================================
 */

#ifndef DEF_NOTES
#define DEF_NOTES

/** =======================================================================
 *	ENUMS
 *  =======================================================================
 */
enum note {
	// First octave
	Do1 		= 1,
	Do1_d		= 2,
	Re1			= 3,
	Re1_d		= 4,
	Mi1			= 5,
	Fa1			= 6,
	Fa1_d		= 7,
	Sol1		= 8,
	Sol1_d 		= 9,
	La1			= 10,
	Si1_b		= 11,
	Si1			= 12,

	// Second octave
	Do2 		= 13,
	Do2_d		= 14,
	Re2			= 15,
	Re2_d		= 16,
	Mi2			= 17,
	Fa2			= 18,
	Fa2_d		= 19,
	Sol2		= 20,
	Sol2_d		= 21,
	La2			= 22,
	Si2_b		= 23,
	Si2			= 24,

	// Third octave
	Do3 		= 25,
	Do3_d		= 26,
	Re3			= 27,
	Re3_d		= 28,
	Mi3			= 29,
	Fa3			= 30,
	Fa3_d		= 31,
	Sol3		= 32,
	Sol3_d		= 33,
	La3			= 34,
	Si3_b		= 35,
	Si3			= 36,

	// Fourth octave
	Do4 		= 37,
	Do4_d		= 38,
	Re4			= 39,
	Re4_d		= 40,
	Mi4			= 41,
	Fa4			= 42,
	Fa4_d		= 43,
	Sol4		= 44,
	Sol4_d		= 45,
	La4			= 46,
	Si4_b		= 47,
	Si4			= 48,

	// Fifth octave
	Do5 		= 49,
	Do5_d		= 50,
	Re5			= 51,
	Re5_d		= 52,
	Mi5			= 53,
	Fa5			= 54,
	Fa5_d		= 55,
	Sol5		= 56,
	Sol5_d		= 57,
	La5			= 58,
	Si5_b		= 59,
	Si5			= 60,

	// Sixth octave
	Do6 		= 61,
	Do6_d		= 62,
	Re6			= 63,
	Re6_d		= 64,
	Mi6			= 65,
	Fa6			= 66,
	Fa6_d		= 67,
	Sol6		= 68,
	Sol6_d		= 69,
	La6			= 70,
	Si6_b		= 71,
	Si6			= 72,

	// Seventh octave
	Do7 		= 73,
	Do7_d		= 74,
	Re7			= 75,
	Re7_d		= 76,
	Mi7			= 77,
	Fa7			= 78,
	Fa7_d		= 79,
	Sol7		= 80,
	Sol7_d		= 81,
	La7			= 82,
	Si7_b		= 83,
	Si7			= 84,

	// Eight octave
	Do8			= 85,
	Do8_d		= 86,
	Re8			= 87,
	Re8_d		= 88,
	Mi8			= 89,
	Fa8			= 90,
	Fa8_d		= 91,
	Sol8		= 92,
	Sol8_d		= 93,
	La8			= 94,
	Si8_b		= 95,
	Si8			= 96
};

/** =======================================================================
 *	SONGS BUILDING DEFINE (Enable data compression on the memory).
 *  =======================================================================
 */

#define _REG_FROM_PARAM(duration, volume, note) \
	((duration & 0xFF) << 16) | ((volume & 0xFF) << 8) | (note & 0xFF)

/** =======================================================================
 *	SONGS PARAMETERS
 *  =======================================================================
 */
// Volume control
#define DEFAULT_VOLUME 			1
#define MUTED 					0

// Notes interval
#define INTERVAL				2 // 20 ms between notes

// Sub defines
#define SMALL_VOLUME 			((DEFAULT_VOLUME / 4) * 2)
#define MEDIUM_VOLUME 			((DEFAULT_VOLUME / 4) * 3)
#define HIGH_VOLUME 			((DEFAULT_VOLUME / 4) * 5)
#define FULL_VOLUME 			((DEFAULT_VOLUME / 4) * 6)

#endif /* DEF_NOTES */
