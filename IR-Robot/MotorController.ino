

#ifndef MotorController_h
#define MotorController_h 

class MotorController {
	private:
		int speed_pin, input1, input2;
		bool direction;
	public:
		void setup();
		void changeDirection();
		void setSpeed(int speed);
		MotorController(int speed_pin_arg, int input1_arg, int input2_arg) {
			speed_pin = speed_pin_arg;
			input1 = input1_arg;
			input2 = input2_arg;
			direction = true;
}
		
}; 

void MotorController::setup() {
	pinMode(speed_pin , OUTPUT);
	pinMode(input1, OUTPUT);
	pinMode(input2, OUTPUT);
}

void MotorController::changeDirection() {
	if(direction) {
		digitalWrite(input1, HIGH);
		digitalWrite(input2, LOW);
	} else {
		digitalWrite(input1, LOW);
		digitalWrite(input2, HIGH);
	}
	direction = !direction;
}

void MotorController::setSpeed(int speed) {
	analogWrite(speed_pin, speed); // Any value between 0 and 255
}

#endif
