#pragma once

#include <Arduino.h>
#include "Pad.h"
#include "_types.h"

#define MAX_PADS 16

#define FAST_ADC true

class ArduinoDrum{

private:
	
	Pad* pad[MAX_PADS];
	int cachedSize;

public:

	// Constructor
	ArduinoDrum();

	// Adds a Pad in the first available slot
	// Returns if a Pad could be added or not, though reading is optional
	bool addPad(Pad* newPad);

	// Remove the Pad (given the ID or Pad*)
	void remove(int id);
	void remove(Pad* pad);

	// Remove all Pads
	void clear();

	// Return the quantity of Pads
	int size();

	// Return the Pad with ID = id
	// Return NULL if none found
	Pad* get(int id);

	// Initializes Serial Communication
	// if changeSpeedADC is 'true', set ADC prescaler to 8
	void begin(unsigned long baudRate, bool changePrescalerADC = false);

	// Main function
	// Chooses between reading pads with or without interface
	void play();

	// Performs pad reading process
	void readPads();

};

extern ArduinoDrum Drum;