#pragma once

#include <Arduino.h>
#include "_types.h"

#define DIGITAL 	true
#define ANALOGIC	false

class Pad{

private:

	String padName;
	int padID;
	int padNote;
	int padType;
	int padPin;
	int padThresholdMin;
	int padThresholdMax;
	int padScanTime;
	int padMaskTime;
	int padMode;

	int readSensor;
	int readNumber;
	int readPeak;
	bool readEnable;
	int velocity;
	unsigned long currentTime;
	unsigned long previousTime;

	// Function Callback
	void (*_callback)(void);
	
public:
	
	// == Constructors == //
	Pad(String name, int note, int pin, int type = PIEZO);
	Pad(String name, int note, int pin, int thresholdMin, int scantime, int maskTime);
	Pad(String name, int note, int pin, bool mode, int type = PIEZO);

	// Initialize pin
	void begin();

	// Read the pins and send the midi note
	void play();

	// Set Callback
	void setCallback(void (*callback)(void));

	// === Getters and Setters === //
	void setName(String newName);
	String getName();

	void setID(int newID);	// Do not use this method without knowing what you are doing
	int getID();

	void setNote(int newNote);
	int getNote();

	void setType(int newType);
	int getType();

	void setPin(int newPin);
	int getPin();

	void setThresholdMin(int newThresholdMin);
	int getThresholdMin();

	void setThresholdMax(int newThresholdMax);
	int getThresholdMax();

	void setScanTime(int newScanTime);
	int getScanTime();

	void setMaskTime(int newMaskTime);
	int getMaskTime();
};