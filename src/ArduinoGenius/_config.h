#pragma once

#include "_tones.h"

// == Piezos pins == //
#define PIEZO_A	A0
#define PIEZO_B	A1
#define PIEZO_C	A2
#define PIEZO_D	A3
#define PIEZO_E	A4

// == Led pins == //
#define LED_A	2
#define LED_B	3
#define LED_C	4
#define LED_D	5
#define LED_E	6

// == Buzzer == //
#define BUZZER	12
#define NOTE_A	NOTE_E4
#define NOTE_B	NOTE_B4
#define NOTE_C	NOTE_G5
#define NOTE_D	NOTE_E5
#define NOTE_E	NOTE_B5


// == Genius Propertys = //
#define QUANTITY_OF_BUTTONS 5
#define SEQUENCE_SIZE 12


// == Serial == //
// #define DEBUG			// un/comment to enable/disable Serial
#define SERIAL_SPEED	9600
#define NEW_LINE	"\n"
#define TAB 		"\t"
#ifdef DEBUG
	#define LOG 			Serial.print
	#define SerialBegin 	Serial.begin
#else
	#define LOG
	#define SerialBegin
#endif
