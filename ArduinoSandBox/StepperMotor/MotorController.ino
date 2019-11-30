#ifndef MotorController_h
#define MotorController_h 
#define HIGH 1024
#define LOW 0
#define MAX_SPEED_INDICATOR_ESP 1024
#define MAX_SPEED_INDICATOR_ARD 255
#define DC_FREQUENCY 10000


class MotorController {
	private:
		SpeedController speedController;	
		int stepsPerMeter, encoderA, encoderB;
		int input1, input2, speed_pin, maxSpeed;
		ArduinoUtilController util;
		void changeDirection(boolean isForward);
		void normailzeData(int data);
		void display(int x);
		void drive(boolean isForward, int speed);
	public:
		void setup();
		void stop();
		void setSpeed(int speed);
		MotorController(){}
		MotorController(int input1_arg, int input2_arg, int sencor1_arg, int sencor2_arg, int stepsPerMeter_arg = 1200) {
			input1 = input1_arg;
			input2 = input2_arg;
			encoderA = sencor1_arg; 
			encoderB = sencor2_arg;
			stepsPerMeter =stepsPerMeter_arg;
		}
}; 

void MotorController::setup() {
	speedController.setup(encoderA, encoderB, stepsPerMeter);
	pinMode(input1, OUTPUT);
	pinMode(input2, OUTPUT);

	if(ENVIRONMENT == "arduino") {

		// TCCR2B = TCCR2B & B11111000 | B00000001; // for PWM frequency of 31372.55 Hz
		// TCCR2B = TCCR2B & B11111000 | B00000010; // for PWM frequency of 3921.16 Hz
		// TCCR2B = TCCR2B & B11111000 | B00000011; // for PWM frequency of 980.39 Hz
		// TCCR2B = TCCR2B & B11111000 | B00000100; // for PWM frequency of 490.20 Hz (The DEFAULT)
		// TCCR2B = TCCR2B & B11111000 | B00000101; // for PWM frequency of 245.10 Hz
		// TCCR2B = TCCR2B & B11111000 | B00000110; // for PWM frequency of 122.55 Hz
		TCCR2B = TCCR2B & B11111000 | B00000111; // for PWM frequency of 30.64 Hz

		TCCR0B = TCCR0B & B11111000 | B00000101; // for PWM frequency of 61.04 Hz

		maxSpeed = MAX_SPEED_INDICATOR_ARD;
	} else {
		maxSpeed = MAX_SPEED_INDICATOR_ESP;
		//analogWriteFreq(30);
	}
	drive(true, 0);
}

void MotorController::setSpeed(int speed) {
	bool direction = speed > 0;
	speed = abs(speed);
	normailzeData(speed);

	stop();
	drive(direction, speed); //max speed Arduino: 255 ESP:1024
}

void MotorController::stop() {
	analogWrite(input1, LOW);
	analogWrite(input2, LOW);
}

void MotorController::normailzeData(int data) {
	if(data > maxSpeed) {
		data = maxSpeed;
	}
}

void MotorController::drive(boolean isForward, int speed = 1024) {
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
