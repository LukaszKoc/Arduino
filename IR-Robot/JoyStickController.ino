#ifndef JoyStickController_h
#define JoyStickController_h 

class JoyStickController {
	private:
		void setup();
	public:
		void readInput(InputXYS *joyInput);
		JoyStickController() {
			setup();
		}
}; 

void JoyStickController::setup() {
	pinMode(JS_SW_pin, INPUT);
	digitalWrite(JS_SW_pin, HIGH);
	Serial.begin(115200);
}

void JoyStickController::readInput(InputXYS *joyInput) {
	joyInput->x = analogRead(JS_X_pin);
	joyInput->y = analogRead(JS_Y_pin), 
	joyInput->s = digitalRead(JS_SW_pin);

	// joyInput.setX(analogRead(JS_X_pin));
	// joyInput.setY(analogRead(JS_Y_pin)), 
	// joyInput.setS(digitalRead(JS_SW_pin));
}

#endif