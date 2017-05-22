#pragma once

#include "_config.h"

void generateSequence(int* randomSequence){

	randomSeed(analogRead(A5));

	for (int i = 0; i < SEQUENCE_SIZE; i++){

		randomSequence[i] = random(QUANTITY_OF_BUTTONS);

      	LOG(randomSequence[i]);
      	LOG("  ");

	}
	LOG(NEW_LINE);
}