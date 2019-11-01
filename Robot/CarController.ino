#ifndef CarController_h
#define CarController_h 


class CarController {
	private:
		ArduinoUtilController util;
		MotorController motorLeft, motorRight;
		int speedL, speedR;
		const String LEFT = "LEFT";
		const String RIGHT = "RIGHT";
		String calculateDirection(int arq);
		void display(int x, int y, int z = -1);
	public:
		void drive(int speed, int arq);
		CarController(MotorController _motorLeft, MotorController _motorRight) {
			motorLeft = _motorLeft;
			motorRight = _motorRight;
		}
}; 


void CarController::drive(int speed, int turn) {
		int speedRight;
		int speedLeft;
		int arqSpeed = 50;
	if(speed > -20 && speed < 20) {
		speedRight = 0;
		speedLeft = 0;
	} else {
		if(turn > -50 && turn < 50) {
			speedRight = speed;
			speedLeft = speed ;
		} else {
			speed = speed - 50;
			if(calculateDirection(turn) == RIGHT) {
				speedRight = speed - arqSpeed;
				speedLeft = speed + arqSpeed;
			} else {
				speedRight = speed + arqSpeed;
				speedLeft = speed - arqSpeed;		
			}
		}
	}
	motorRight.setSpeed(speedRight);
	motorLeft.setSpeed(speedLeft);
}


String CarController::calculateDirection(int turn){
	if(turn >= 0){ return RIGHT;}
	return LEFT;
}

#endif