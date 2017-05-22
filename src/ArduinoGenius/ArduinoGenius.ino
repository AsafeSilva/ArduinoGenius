#include "_config.h"
#include "_tones.h"
#include "Random.h"
#include "ArduinoDrum.h"


// == Prototype of the callback functions == //
void playA();
void playB();
void playC();
void playD();
void playE();

#define RELEASE -1
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4

// == Genius variables == //
int randomSequence[SEQUENCE_SIZE];
typedef void (*Callbacks)(void);
int index = 0;
int calledFunction = RELEASE;
bool hasWon = true;
Callbacks piezos[] = {
	playA, playB, playC,
	playD, playE
};
#define DELAY_MIN 150
#define DELAY_MAX 350
int timeLevel = DELAY_MAX;

// == Piezos variables == //
#define THRESH_MIN	200
#define SCAN_TIME	100
#define MASK_TIME	300

Pad btnA("A", NOTE_A, PIEZO_A, THRESH_MIN, SCAN_TIME, MASK_TIME);
Pad btnB("B", NOTE_B, PIEZO_B, THRESH_MIN, SCAN_TIME, MASK_TIME);
Pad btnC("C", NOTE_C, PIEZO_C, THRESH_MIN, SCAN_TIME, MASK_TIME);
Pad btnD("D", NOTE_D, PIEZO_D, THRESH_MIN, SCAN_TIME, MASK_TIME);
Pad btnE("E", NOTE_E, PIEZO_E, THRESH_MIN, SCAN_TIME, MASK_TIME);


void setup(){

	// Setup Serial Communication
	SerialBegin(SERIAL_SPEED);

	// Setup piezos
	btnA.setCallback(playA);
	btnB.setCallback(playB);
	btnC.setCallback(playC);
	btnD.setCallback(playD);
	btnE.setCallback(playE);

	Drum.addPad(&btnA);
	Drum.addPad(&btnB);
	Drum.addPad(&btnC);
	Drum.addPad(&btnD);
	Drum.addPad(&btnE);

	// Sets pins of the LEDs as output
	pinMode(LED_A, OUTPUT);
	pinMode(LED_B, OUTPUT);
	pinMode(LED_C, OUTPUT);
	pinMode(LED_D, OUTPUT);
	pinMode(LED_E, OUTPUT);

	// Generates new random sequence
	generateSequence(randomSequence);
	
}


void loop(){

	// Plays sequence until index
	playSequence();
	calledFunction = RELEASE;

	// Expect touches
	for (int i = 0; i <= index; i++){
		LOG("Esperando toque!\n");
		while(calledFunction == RELEASE){ 
			// Process of reading the piezos
			Drum.play();
		}

		// Correct note!
		if(calledFunction == randomSequence[i]){
			calledFunction = RELEASE;
			LOG("Acertou a nota!\n");
		}
		// Missed!	
		else{
			hasWon = false;
			LOG("Errou a nota!\n");
			break;
		}
	}

	if(hasWon == true){
		index++;
		// Won the game!
		if(index == SEQUENCE_SIZE){
			index = 0;
			delay(1000);
			YouWon();
			generateSequence(randomSequence);

			timeLevel -= DELAY_MIN;
			if(timeLevel < DELAY_MIN) timeLevel = DELAY_MAX;

		// Won the stage!
		}else{
			delay(1000);
			Hit();
		}

	// Restart game!	
	}else{
		timeLevel = DELAY_MAX;
		index = 0;
		hasWon = true;
		delay(1000);
		Missed();
		generateSequence(randomSequence);
	}

	delay(1000);	
}

void playSequence(){
	for (int i = 0; i <= index; i++){
		piezos[randomSequence[i]]();
		delay(timeLevel);
	}
}

void playA(){
	LOG("A"); LOG(NEW_LINE);
	digitalWrite(LED_A, 1);
	tone(BUZZER, NOTE_A, 200);
	delay(100);
	digitalWrite(LED_A, 0);
	calledFunction = A;
}

void playB(){
	LOG("B"); LOG(NEW_LINE);
	digitalWrite(LED_B, 1);
	tone(BUZZER, NOTE_B, 200);
	delay(100);
	digitalWrite(LED_B, 0);
	calledFunction = B;
}

void playC(){
	LOG("C"); LOG(NEW_LINE);
	digitalWrite(LED_C, 1);
	tone(BUZZER, NOTE_C, 200);
	delay(100);
	digitalWrite(LED_C, 0);
	calledFunction = C;
}

void playD(){
	LOG("D"); LOG(NEW_LINE);
	digitalWrite(LED_D, 1);
	tone(BUZZER, NOTE_D, 200);
	delay(100);
	digitalWrite(LED_D, 0);
	calledFunction = D;
}

void playE(){
	LOG("E"); LOG(NEW_LINE);
	digitalWrite(LED_E, 1);
	tone(BUZZER, NOTE_E, 200);
	delay(100);
	digitalWrite(LED_E, 0);
	calledFunction = E;
}

void YouWon(){
	LOG("Parabens, voce venceu!\n");

	playA(); playB(); playC(); playD();
	playE(); playD(); playC(); playB();
	playE(); playD(); playC(); playB();
	playA();
}

void Hit(){
	LOG("Parabens, vamos para proxima fase!\n");

	playA(); playB(); playC(); playD(); playE();
}

void Missed(){
	LOG("Voce perdeu!\n");

	playE(); playD(); playC(); playB(); playA();
}
