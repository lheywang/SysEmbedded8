# SysEmbedded8

NIOS II + Embedded C developpement project, for school

## Requirements : 
- Show hour
- Trigger a melody play once it's time
- Enable some settings

## Buttons assignements

### Switchs
- SW9 : 	|
- SW8 : 	| 	--> Melody selection (1)
- SW7 : 	|
- SW6 : 	|
- SW5 : 	|	--> Hex display luminosity (1 to 8)
- SW4 : 	|
- SW3 : 		--> Hour format	
- SW2 : 		--> Alarm hour configuration
- SW1 : 		--> Time configuration
- SW0 : 		--> Alarm ON / OFF (OFF = cut song !)

### Buttons
- BP0 :			--> Short pulse : 	+ 1s
				--> Long pulse :  	+ 1s / + 10s / + 1 mn (gradually)
- BP1 : 		--> Short pulse : 	+ 1 mn
				--> Long pulse :	+ 1 mn / + 10 mn / + 1h

## Available melodies
- 000 :			--> Elise's letter
- 001 :			--> Astronomia / Coffins dance
- 010 : 		--> Crazy Frog
- 011 :			--> Baby Shark
- 100 :
- 101 : 
- 110 : 
- 111 : 

## Leds
- LEDR9 :		--> Blink at 1 Hz when alarm is ringing
- LEDR8 : 
- LEDR7 : 
- LEDR6 :
- LEDR5 :
- LEDR4 :
- LEDR3 :
- LEDR2 :
- LEDR1 :
- LEDR0 :		--> Blink at 0.2 Hz (500 ms on, 4.5s off) when alarm is enabled

## Known issues
### Bugs
- Selecting hour / alarm does not work
- Cannot set up alarm

### To test
- Alarm ringing

