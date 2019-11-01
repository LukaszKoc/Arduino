

#ifndef MotorController_h
#define MotorController_h 

class MotorController {
	private:
		int speed_pin, input1, input2;
		ArduinoUtilController util;
		void changeDirection(boolean isForward);
		void display(int speed);
		void stop();
	public:
		void setup();
		void setSpeed(int speed);
		MotorController(){}
		MotorController(int speed_pin_arg, int input1_arg, int input2_arg) {
			speed_pin = speed_pin_arg;
			input1 = input1_arg;
			input2 = input2_arg;
}
		
}; 


void MotorController::setSpeed(int speed) {
	changeDirection(speed > 0);

	speed = abs(speed);
	if(speed < 50) {
		stop();
	} else if(speed > 255) {
		speed = 255;
	}

	analogWrite(speed_pin, speed); // Any value between 0 and 255
}

void MotorController::stop() {
	analogWrite(speed_pin, 0);
	digitalWrite(input1, LOW);
	digitalWrite(input2, LOW);
}
void MotorController::changeDirection(boolean isForward) {
	
	if(isForward) {
	Serial.print(" ");
		digitalWrite(input1, HIGH);
		digitalWrite(input2, LOW);
	} else {
	Serial.print("-");
		digitalWrite(input1, LOW);
		digitalWrite(input2, HIGH);
	}
}

void MotorController::setup() {
	pinMode(speed_pin , OUTPUT);
	pinMode(input1, OUTPUT);
	pinMode(input2, OUTPUT);
	changeDirection(true);
}


void MotorController::display(int x) {
	Serial.print("\n\tMotor:\t");
	Serial.print(x);
}
#endif
