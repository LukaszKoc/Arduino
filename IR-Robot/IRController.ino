#ifndef IRController_h
#define IRController_h 

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

class IRController {
	private:
		void iRInputActionPerformner(int inputCode);
		void setup();
	public:
		int readIRInputCode();
		void handleIrInput(int inputCode);
		IRController() {
			setup();
		}
}; 

void IRController::setup() {
	Serial.begin(9600);
	irrecv.enableIRIn();
	irrecv.blink13(true);
}

int IRController::readIRInputCode() {
	int inputCode = -1;
	 if (irrecv.decode(&results)) {
		inputCode =	results.value;
		irrecv.resume();
	}
	return inputCode;
}

#endif