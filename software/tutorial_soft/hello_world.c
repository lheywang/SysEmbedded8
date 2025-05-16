/* This program demonstrates use of parallel ports in the Computer System, It displays a
rotating pattern on the LEDs and HEXs:
* 1. if a KEY0 is pressed, LEDs uses SW positions as a pattern
* 2. if a KEY1 is pressed, HEXs uses inverted SW positions as a pattern */
#include "system.h"
#include "alias.h"
#include "hex/hex.h"

#include <stdio.h>
#include <unistd.h>
#include <math.h>

static void initial_message(){ printf("\n\n***CE PROGRAMME UTILISE DES MACROS***\n"); }

/* MAIN FUNCTION */
int main(void) {

	int HEX_bits = 0x0; // initial pattern for HEX displays
	int LED_bits = 0x0; // initial pattern for LED lights
	int SW_value; //, KEY_value;
	int press, delay_count = 0;
	float res = 0.0;
	int round_res = 0;

	int Op1 = 0, Op2 = 0;
	int Op = 0xFF;

	char hexval[4];

	initial_message();

	while (1)
	{
		// Read the value
		SW_value = SW_IORD_DATA;
		Op1 = SW_value & 0x01F;
		Op2 = (SW_value & 0x3e0) >> 5;

		Op = BP_IORD_DATA & 0x03;
		BP_IOWR_EDGE(Op); // Clear the edge register

		printf("DBG-INF <Input> Op1 %d, Op2 %d, Op %d \n", Op1, Op2, Op);

		switch (Op)
		{
		case 0 :
		{
			res = (float)((float)Op1 + (float)Op2);
			printf("DBG-INF <Loop> res %d \n", (int)(res * 100));

			round_res = (int)floor(res);
			res = res - (float)round_res;

			LEDR_IOWR_DATA(res * 1024);
			printf("DBG-INF <Loop> remains %d \n", (int)(res * 1024));

			sprintf(&hexval, "%04d", round_res);
			hex_display(hexval, 4, 0);

			break;
		}
		case 1 :
		{
			res = (float)((float)Op1 - (float)Op2);
			printf("DBG-INF <Loop> res %d \n", (int)(res * 100));

			round_res = (int)floor(res);
			res = res - (float)round_res;

			sprintf(&hexval, "%04d", round_res);
			hex_display(hexval, 4, 0);

			LEDR_IOWR_DATA(res * 1024);
			printf("DBG-INF <Loop> remains %d \n", (int)(res * 1024));

			break;
		}
		case 2 :
		{
			res = (float)((float)Op1 * (float)Op2);
			printf("DBG-INF <Loop> res %d \n", (int)(res * 100));

			round_res = (int)floor(res);
			res = res - (float)round_res;

			sprintf(&hexval, "%04d", round_res);
			hex_display(hexval, 4, 0);

			LEDR_IOWR_DATA(res * 1024);
			printf("DBG-INF <Loop> remains %d \n", (int)(res * 1024));

			break;
		}
		case 3 :
		{
			res = (float)((float)Op1 / (float)Op2);
			printf("DBG-INF <Loop> res %d \n", (int)(res * 100));

			round_res = (int)floor(res);
			res = res - (float)round_res;

			sprintf(&hexval, "%04d", round_res);
			hex_display(hexval, 4, 0);

			LEDR_IOWR_DATA(res * 1024);
			printf("DBG-INF <Loop> remains %d \n", (int)(res * 1024));

			break;
		}
		default:
		{
			hex_display("----", 4, 0);
			break;
		}
		}

		// Delay
		for (delay_count = 200000; delay_count != 0; --delay_count);
		}
}
