#ifndef JoyStickController_h
#define JoyStickController_h 

class JoyStickController {
	private:
		int xPin, yPin, sPin;
	public:
		void setup();
		int readX();
		int readY();
		int readS();
		JoyStickController(int xPin_arg, int yPin_arg, int sPin_arg) {
			xPin = xPin_arg; 
			yPin = yPin_arg;
			sPin = sPin_arg;
		}
}; 

void JoyStickController::setup() {
	pinMode(sPin, INPUT);
	digitalWrite(sPin, HIGH);
}

int JoyStickController::readX() {
	return analogRead(xPin);
}
int JoyStickController::readY() {
	return analogRead(yPin); 
}
int JoyStickController::readS() {
	return digitalRead(sPin);
}

#endif