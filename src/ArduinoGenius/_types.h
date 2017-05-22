#pragma once

// Uncomment if you don't use interface
// #define USING_INTERFACE

// === Notes (Addictive Drums) === // 
#define HH_CONTROLLER	4
#define SNARE 			38
#define SNARE_SIDESTICK 42
#define KICK 			36
#define TOM1 			71
#define TOM2 			69
#define TOM3 			67
#define TOM4 			65
#define HIHAT 			8
#define CYMBAL1 		77
#define CYMBAL2 		79
#define CYMBAL3 		81
#define RIDE_TIPE 		60
#define RIDE_BELL 		61

// === Types === //
#define PIEZO 	144
#define HH_C 	176
#define OFF 	128

// Define number of midi channel
#define MIDI_CHANNEL 0

// Define maximum value of property
#define NOTE_MAX		127
#define SENSIT_MAX		1023
#define THRESHMIN_MAX	1023
#define THRESHMAX_MAX	1023
#define SCANTIME_MAX	5000
#define MASKTIME_MAX	5000

// Defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// == Encoder Pins == //
#define ENC_A		2		// ENC_A must be a pin of External Interrupt
#define ENC_B		4
#define ENC_ENTER	3 		// ENC_ENTER must be a pin of External Interrupt

// == Pins LCD == //
// #define LCD_RW		GND
#define	LCD_RS		10
#define	LCD_EN		9
#define	LCD_D4		8
#define	LCD_D5		7
#define	LCD_D6		6
#define	LCD_D7		5
