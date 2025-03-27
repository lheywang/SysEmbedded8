/* This program demonstrates use of parallel ports in the Computer System, It displays a
rotating pattern on the LEDs and HEXs:
* 1. if a KEY0 is pressed, LEDs uses SW positions as a pattern
* 2. if a KEY1 is pressed, HEXs uses inverted SW positions as a pattern */
#include "system.h"
#include "alias.h"

#include <stdio.h>
#include <unistd.h>

static void initial_message(){ printf("\n\n***CE PROGRAMME UTILISE DES MACROS***\n"); }

/* MAIN FUNCTION */
int main(void) {

	int HEX_bits = 0x0; // initial pattern for HEX displays
	int LED_bits = 0x0; // initial pattern for LED lights
	int SW_value; //, KEY_value;
	int press, delay_count = 0;

	initial_message();

	while (1)
	{
		SW_value = SW_IORD_DATA; // read the SW slider switch values
		press = BP_IORD_EDGE; // read the pushbutton edge capture register
		BP_IOWR_EDGE(press); // Clear the edge capture register

		if (press & 0x1) // KEY0 pressed
		LED_bits = SW_value; // set LEDs pattern using SW values

		if (press & 0x2) // KEY1 pressed
		HEX_bits = ~SW_value; // set HEX pattern using SW values

		HEX_IOWR_DATA(HEX_bits); // display pattern on HEX3 ... HEX0
		LEDR_IOWR_DATA(LED_bits); // display leds

		if (HEX_bits & 0x80000000) HEX_bits = (HEX_bits << 1) | 1;
		else HEX_bits = HEX_bits << 1;

		if (LED_bits & 0x00000001) LED_bits = (LED_bits >> 1) | 0x80000000;
		else LED_bits = (LED_bits >> 1) & 0x7FFFFFFF;

		for (delay_count = 200000; delay_count != 0; --delay_count); // delay loop
		}
}
