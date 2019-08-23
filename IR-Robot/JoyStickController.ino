#ifndef JoyStickController_h
#define JoyStickController_h 

class JoyStickController {
	private:
	public:
		void setup();
		int readX();
		int readY();
		int readS();
		JoyStickController() {
		}
}; 

void JoyStickController::setup() {
	pinMode(JS_SW_pin, INPUT);
	digitalWrite(JS_SW_pin, HIGH);
}

int JoyStickController::readX() {
	return analogRead(JS_X_pin);
}
int JoyStickController::readY() {
	return analogRead(JS_Y_pin); 
}
int JoyStickController::readS() {
	return digitalRead(JS_SW_pin);
}

#endif