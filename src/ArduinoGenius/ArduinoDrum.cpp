#include "ArduinoDrum.h"


ArduinoDrum::ArduinoDrum(){
	cachedSize = 0;

	clear();
}


bool ArduinoDrum::addPad(Pad* newPad){
	// Check if the Pad already exists on the array
	for(int i = 0; i < MAX_PADS; i++){
		if(pad[i] != NULL && pad[i]->getPin() == newPad->getPin())
			return true;
	}

	// Find an empty space to put the new Pad
	for(int i = 0; i < MAX_PADS; i++){
		if(!pad[i]){
			// Add new Pad
			pad[i] = newPad;
			pad[i]->setID(i);
			pad[i]->begin();
			cachedSize++;
			return true;
		}
	}

	// Array is full
	return false;
}

void ArduinoDrum::remove(int id){
	// Find a Pad with ID, and removes
	for(int i = 0; i < MAX_PADS; i++){
		if(pad[i]->getID() == id){
			pad[i] = NULL;
			cachedSize--;
			return;
		}
	}
}

void ArduinoDrum::remove(Pad* pad){
	remove(pad->getID());
}

void ArduinoDrum::clear(){
	for(int i = 0; i < MAX_PADS; i++)
		pad[i] = NULL;

	cachedSize = 0;
}

int ArduinoDrum::size(){
	return cachedSize;
}

Pad* ArduinoDrum::get(int id){

	if(id >= MAX_PADS) return NULL;

	int pos = -1;
	for(int i = 0; i < MAX_PADS; i++){
		if(pad[i] != NULL){
			pos++;

			if(pos == id)
				return pad[i];
		}
	}

	return NULL;
}

void ArduinoDrum::begin(unsigned long baudRate, bool changePrescalerADC){

	Serial.begin(baudRate);

	if(changePrescalerADC){
		// set prescale to 8
		cbi(ADCSRA, ADPS2);
		sbi(ADCSRA, ADPS1);
		sbi(ADCSRA, ADPS0);		
	}

	#ifdef USING_INTERFACE
	Interface.begin();
	#endif

}

void ArduinoDrum::play(){
#ifndef USING_INTERFACE
	readPads();
#else
	Interface.runInterface();
#endif

}

void ArduinoDrum::readPads(){
	for(int i = 0; i < MAX_PADS; i++){
		if(pad[i] == NULL)	continue;
		
		pad[i]->play();
	}
}

// === Preinstantiate Object === //
ArduinoDrum Drum = ArduinoDrum();
