#ifndef IRController_h
#define IRController_h 

IRrecv irrecv(IR_RECV_PIN);
decode_results results;

class IRController {
	private:
	public:
		void setup();
		int readIRInputCode();
		void handleIrInput(int inputCode);
		IRController() {
		}
}; 

void IRController::setup() {
	irrecv.blink13(true);
	irrecv.enableIRIn();
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