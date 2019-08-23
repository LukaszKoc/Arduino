
#include <IRremote.h>
#include <SoftwareSerial.h>
#include <TM1637Display.h>

#include "IRController.ino"
#include "DisplayController.ino"

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

IRController iRController;
DisplayController displayController;

void setup() {
	Serial.begin(9600);
	irrecv.enableIRIn();
	irrecv.blink13(true);
}

void loop() {
	iRController.handleIrInput(readIRInputCode());
}

int readIRInputCode () {
	int inputCode = -1;
	 if (irrecv.decode(&results)) {
		inputCode =	results.value;
		irrecv.resume();
	}
	return inputCode;
} 

