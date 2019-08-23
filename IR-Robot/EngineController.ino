#ifndef IRController_h
#define IRController_h 

class IRController {
	private:
		void driveForward();
		void iRInputActionPerformner(int inputCode);

	public:
		IRController(){}
		void handleIrInput(int inputCode);
}; 

void IRController::handleIrInput(int inputCode) {
	iRInputActionPerformner(inputCode);
}

void IRController::iRInputActionPerformner(int inputCode) {

	switch(inputCode) {
		case 0xFF18E7: //BUTTON_UP
		Serial.print("IR input BUTTON_UP");
			//TODO perform action 
			driveForward();
		break;
		case 0xFF4AB5: //BUTTON_DOWN
			Serial.print("IR input BUTTBUTTON_DOWNON_UP");
			//TODO perform action 
		break;
		case 0xFF10EF: //BUTTON_LEFT
			Serial.print("IR input BUTTON_LEFT");
			//TODO perform action 
		break;
		case 0xFF5AA5: //BUTTON_RIGHT
			Serial.print("IR input BUTTON_RIGHT");
			//TODO perform action 
		break;
		case -1: //error
			Serial.print("IR input unknown button ");
			//TODO perform action 
		break;
	}
}

void IRController::driveForward() {

}

#endif