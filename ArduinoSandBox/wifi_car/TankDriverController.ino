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
	public:
		void drive(int x, int y);
		TankDriverController(MotorController _motorLeft, MotorController _motorRight, boolean _singleJoystickMode = true) {
			motorLeft = _motorLeft;
			motorRight = _motorRight;
			singleJoystickMode = _singleJoystickMode;
		}
};


void TankDriverController::drive(int x, int y) {
	int speedRight, speedLeft;

	speedLeft = x;
	speedRight = x;
	
	// if(x < 150) {
	// 	if(y > 80) {
	// 		speedLeft = -150;
	// 		speedRight = 150;
	// 	} else if(y < -80) {
	// 		speedLeft = 150;
	// 		speedRight = -150;
	// 	}
	// } else {
	// 	if(y > 80) {
	// 		speedLeft = x - y;
	// 		speedRight = x + y;
	// 	} else if(y < -80) {
	// 		speedLeft = x - y;
	// 		speedRight = x + y;
	// 	}
	// }

	if(speedLeft > 250 || speedRight> 250) {
		
	}

	
	speedLeft = map(speedLeft, 0, 100, 0, 1024);
	speedRight = map(speedRight, 0, 100, 0, 1024);
	motorLeft.setSpeed(speedLeft);
	motorRight.setSpeed(speedRight);
}


String TankDriverController::calculateDirection(int turn) {
	if(turn >= 0){ return RIGHT;}
	return LEFT;
}

#endif