#include "Pad.h"


Pad::Pad(String name, int note, int pin, int type){
	padMode = ANALOGIC;
	setName(name);
	setNote(note);
	setPin(pin);
	setType(type);
	setThresholdMin(150);
	setThresholdMax(1023);
	setScanTime(5);
	setMaskTime(100);

	readSensor = 0;
	readNumber = 0;
	readPeak = 0;
	readEnable = true;
	velocity = 0;
	currentTime = 0;
	previousTime = 0;
}

Pad::Pad(String name, int note, int pin, int thresholdMin, int scantime, int maskTime){
	padMode = ANALOGIC;
	setName(name);
	setNote(note);
	setPin(pin);
	setType(PIEZO);
	setThresholdMin(thresholdMin);
	setThresholdMax(1023);
	setScanTime(scantime);
	setMaskTime(maskTime);

	readSensor = 0;
	readNumber = 0;
	readPeak = 0;
	readEnable = true;
	velocity = 0;
	currentTime = 0;
	previousTime = 0;
}

Pad::Pad(String name, int note, int pin, bool mode, int type){
	padMode = mode;
	setName(name);
	setNote(note);
	setPin(pin);
	setType(type);
	setThresholdMin(150);
	setThresholdMax(1023);
	setScanTime(5);
	setMaskTime(100);

	readSensor = 0;
	readNumber = 0;
	readPeak = 0;
	readEnable = true;
	velocity = 0;
	currentTime = 0;
	previousTime = 0;	
}

void Pad::begin(){
	if(padMode == DIGITAL)
		pinMode(padPin, INPUT_PULLUP);
}

void Pad::play(){
	// analogRead(padPin);
	// delay(10);
	readSensor = analogRead(padPin);

	if((padType != OFF) &&
		(readSensor > padThresholdMin) &&
		((currentTime - previousTime) <= padMaskTime)){

		currentTime = millis();

		if(readNumber < padScanTime){

			if(readSensor > readPeak)
				readPeak = readSensor;

			readNumber++;	

		}else if(readEnable){

			readEnable = false;

			if (readPeak < padThresholdMin)			readPeak = padThresholdMin;
			else if (readPeak > padThresholdMax)	readPeak = padThresholdMax;

			velocity = map(readPeak, padThresholdMin, padThresholdMax, 1, 127);

			// Send Midi Note
			// Serial.write(padType | MIDI_CHANNEL);
			// Serial.write(padNote);
			// Serial.write(velocity);

			// Modifying for the Protheus Genius
			if (_callback != NULL){
				_callback();
				// delay(100);
			}
			

		}
	}else if((currentTime - previousTime) > padMaskTime){
    	readEnable = true;
    	readNumber = 0;
    	readPeak = 0;
    	previousTime = currentTime;		
	}

}

void Pad::setCallback(void (*callback)(void)){
	_callback = callback;
}

// === Getters and Setters === //

void Pad::setName(String newName){	padName = newName;	}
String Pad::getName(){	return padName;	}

void Pad::setID(int newID){	padID = newID;	}
int Pad::getID(){	return padID;	}

void Pad::setNote(int newNote){	padNote = newNote;	}
int Pad::getNote(){	return padNote;	}

void Pad::setType(int newType){	padType = newType;	}
int Pad::getType(){	return padType;	}

void Pad::setPin(int newPin){	padPin = newPin;	}
int Pad::getPin(){	return padPin;	}

void Pad::setThresholdMin(int newThresholdMin){	padThresholdMin = newThresholdMin;	}
int Pad::getThresholdMin(){	return padThresholdMin;	}

void Pad::setThresholdMax(int newThresholdMax){	padThresholdMax = newThresholdMax;	}
int Pad::getThresholdMax(){	return padThresholdMax;	}

void Pad::setScanTime(int newScanTime){	padScanTime = newScanTime;	}
int Pad::getScanTime(){	return padScanTime;	}

void Pad::setMaskTime(int newMaskTime){	padMaskTime = newMaskTime;	}
int Pad::getMaskTime(){	return padMaskTime;	}
