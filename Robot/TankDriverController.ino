#ifndef TankDriverController_h
#define TankDriverController_h 


class TankDriverController {
	private:
		MotorController motorLeft, motorRight;
		int speedL, speedR;
		boolean singleJoystickMode;
		const String LEFT = "LEFT";
		const String RIGHT = "RIGHT";
		String calculateDirection(int arq);
		void display(int x, int y, int z = -1);
	public:
		void drive(int speed, int arq);
		TankDriverController(MotorController _motorLeft, MotorController _motorRight, boolean _singleJoystickMode = true) {
			motorLeft = _motorLeft;
			motorRight = _motorRight;
			singleJoystickMode = _singleJoystickMode;
		}
};


void TankDriverController::drive(int x, int y) {
	int speedRight, speedLeft;

	Serial.print("\n\t\t");
	y = map(y, 0, 255, 0, 100);
	// display(x, y);
	
	speedLeft = x;
	speedRight = x;
	
	if(x < 150) {
		if(y > 80) {
			speedLeft = -150;
			speedRight = 150;
		} else if(y < -80) {
			speedLeft = 150;
			speedRight = -150;
		}
	} else {
		if(y > 80) {
			speedLeft = x - y;
			speedRight = x + y;
		} else if(y < -80) {
			speedLeft = x - y;
			speedRight = x + y;
		}
	}

	if(speedLeft > 250 || speedRight> 250) {
		
		speedLeft = map(speedLeft, 0, max(speedRight, speedLeft), 0, 250);
		speedRight = map(speedRight, 0, max(speedRight, speedLeft), 0, 250);
	}
//	display(speedLeft, speedRight);

	//LED test
	motorLeft.setSpeed(speedLeft);
	motorRight.setSpeed(speedRight);
}


String TankDriverController::calculateDirection(int turn) {
	if(turn >= 0){ return RIGHT;}
	return LEFT;
}


void TankDriverController::display(int x, int y, int z = -1) {
	
	Serial.print(";\t");
	Serial.print(";\t");
	Serial.print(";\t");
	Serial.print(x);
	Serial.print(";\t");
	Serial.print(";\t");
	Serial.print(y);
	if(z != -1) {
		Serial.print(";\t");
		Serial.print(z);
	}
}
#endif