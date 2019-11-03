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
	return map(analogRead(xPin), 0, 1023, 0, 520) - 255;
}
int JoyStickController::readY() {
	return map(analogRead(yPin), 0, 1023, 0, 520) - 255; 
}
int JoyStickController::readS() {
	return - digitalRead(sPin);
}

#endif