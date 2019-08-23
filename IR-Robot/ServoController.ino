#ifndef ServoController_h
#define ServoController_h 

Servo myservo;	// create servo object to control a servo

class ServoController {
	private:
	void setup();
	int currentPosition;
	public:
	void moveToPosition(int newPosition);
	void moveByArc(int arc);
	ServoController() {
		setup();
	}
}; 

void ServoController::setup() {
	myservo.attach(SERVO_INPUT); // attaches the servo on pin 9 to the servo object
}

void ServoController::moveToPosition(int newPosition) {
	if(currentPosition < newPosition) {
		for (int pos = ++currentPosition; pos >= newPosition; pos += 1) {	 // goes from 180 degrees to 0 degrees
			myservo.write(pos);										 // tell servo to go to position in variable 'pos'
			delay(15);													// waits 15ms for the servo to reach the position
		}
	} else {
		for (int pos = --currentPosition; pos <= newPosition; pos -= 1) {	 // goes from 180 degrees to 0 degrees
			myservo.write(pos);										 // tell servo to go to position in variable 'pos'
			delay(15);													// waits 15ms for the servo to reach the position
		}
	}
}

void ServoController::moveByArc(int moveArc) {
	moveToPosition(currentPosition + moveArc);
}

#endif