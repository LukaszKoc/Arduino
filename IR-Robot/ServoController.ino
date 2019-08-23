#ifndef ServoController_h
#define ServoController_h 

Servo myservo;	// create servo object to control a servo

class ServoController {
	private:
	int currentPosition = 10;
	int min = 5;
	int max = 175;
	public:
	void setup();
	void moveToPosition(int newPosition);
	void moveByArc(int arc);
	ServoController() {
	}
}; 

void ServoController::setup() {
	myservo.attach(SERVO_INPUT); // attaches the servo on pin 9 to the servo object
	moveToPosition(currentPosition);
}

void ServoController::moveToPosition(int newPosition) {
	if(currentPosition < newPosition) {
		for (currentPosition; currentPosition <= newPosition && currentPosition < max; currentPosition += 1) {	 // goes from 180 degrees to 0 degrees
			myservo.write(currentPosition);										 // tell servo to go to position in variable 'pos'
			delay(5);													// waits 15ms for the servo to reach the position
		}
	} else {
		for (currentPosition; currentPosition >= newPosition && currentPosition > min; currentPosition -= 1) {	 // goes from 180 degrees to 0 degrees
			myservo.write(currentPosition);										 // tell servo to go to position in variable 'pos'
			delay(5);													// waits 15ms for the servo to reach the position
		}
	}
}

void ServoController::moveByArc(int moveArc) {
	moveToPosition(currentPosition + moveArc);
}

#endif