#ifndef MotorController_h
#define MotorController_h 

class MotorController {
	private:
		int input1, input2;
		ArduinoUtilController util;
		void changeDirection(boolean isForward);
		void display(int x);
		void drive(boolean isForward, int speed);
		void stop();
	public:
		void setup();
		void setSpeed(int speed);
		MotorController(){}
		MotorController(int input1_arg, int input2_arg) {
			input1 = input1_arg;
			input2 = input2_arg;
		}
}; 


void MotorController::setSpeed(int speed) {
	bool direction = speed > 0;
	speed = abs(speed);
	if(speed < 50) {
		stop();
		return;
	} else if(speed > 1024) {
		speed = 1024;
	}

	display(speed);
	drive(direction, speed); //max speed Arduino: 255 ESP:1024
}

void MotorController::stop() {
	digitalWrite(input1, LOW);
	digitalWrite(input2, LOW);
}

void MotorController::drive(boolean isForward, int speed = 1024) {
	if(isForward) {
	Serial.print(" ");
		analogWrite(input1, speed);
		digitalWrite(input2, LOW);
	} else {
	Serial.print("-");
		digitalWrite(input1, LOW);
		analogWrite(input2, speed);
	}
}

void MotorController::setup() {
	pinMode(input1, OUTPUT);
	pinMode(input2, OUTPUT);
	changeDirection(true);
}


void MotorController::display(int x) {
	Serial.print("\n\tMotor:\t");
	Serial.print(x);
}
#endif
