#ifndef ArduinoUtilController_h
#define ArduinoUtilController_h 

class ArduinoUtilController {
	public:
		static void endLoop(int duration);
		static int mathAbs(int value);
	
}; 

void ArduinoUtilController::endLoop(int duration = 500) {
	delay(duration);
	// Serial.print("\n\t\t\t\t\t\t\t\t Loop =====> \n");
}

int ArduinoUtilController::mathAbs(int input) {
	if(input < 0){ return -input;}
	return input;
}
#endif