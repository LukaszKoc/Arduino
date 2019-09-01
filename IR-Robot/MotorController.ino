

#ifndef MotorController_h
#define MotorController_h 

class MotorController {
	private:
		int speed_pin, input1, input2;
	public:
		void setup();
		void changeDirection(boolean isForward);
		void setSpeed(int speed);
		MotorController(int speed_pin_arg, int input1_arg, int input2_arg) {
			speed_pin = speed_pin_arg;
			input1 = input1_arg;
			input2 = input2_arg;
}
		
}; 


void MotorController::changeDirection(boolean isForward) {
	
	if(isForward) {
		digitalWrite(input1, HIGH);
		digitalWrite(input2, LOW);
	} else {
		digitalWrite(input1, LOW);
		digitalWrite(input2, HIGH);
	}
}
void MotorController::setSpeed(int speed) {
	
	changeDirection(speed<0);
	if(speed<0) {speed = -speed;}
	if(speed<50) {speed = 0;}
	if(speed>250) {speed = 250;}

	analogWrite(speed_pin, speed); // Any value between 0 and 255
}


void MotorController::setup() {
	pinMode(speed_pin , OUTPUT);
	pinMode(input1, OUTPUT);
	pinMode(input2, OUTPUT);
	changeDirection(true);
}
#endif
