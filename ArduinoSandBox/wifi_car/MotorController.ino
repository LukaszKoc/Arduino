#ifndef MotorController_h
#define MotorController_h 

#define DC_FREQUENCY 64

class MotorController {
	private:
		int input1, input2, speed_pin;
		ArduinoUtilController util;
		void changeDirection(boolean isForward);
		void display(int x);
		void drive(boolean isForward, int speed);
	public:
		void setup();
		void stop();
		void setSpeed(int speed);
		MotorController(){}
		MotorController(int input1_arg, int input2_arg) {
			input1 = input1_arg;
			input2 = input2_arg;
		}
}; 

void MotorController::setup() {
	analogWriteFreq(DC_FREQUENCY);
	pinMode(input1, OUTPUT);
	pinMode(input2, OUTPUT);
	drive(true, 0);
}

void MotorController::setSpeed(int speed) {
	bool direction = speed > 0;
	speed = abs(speed);
	if(speed < 100) {
		return;
	}
	drive(direction, speed); //max speed Arduino: 255 ESP:1024
}

void MotorController::stop() {
	analogWrite(input1, LOW);
	analogWrite(input2, LOW);
}

void MotorController::drive(boolean isForward, int speed = 1024) {
	stop();
	if(isForward) {
		analogWrite(input1, speed);
		analogWrite(input2, LOW);
	} else {
		analogWrite(input1, LOW);
		analogWrite(input2, speed);
	}
}



void MotorController::display(int x) {
	Serial.print("\n\tMotor:\t");
	Serial.print(x);
}
#endif
