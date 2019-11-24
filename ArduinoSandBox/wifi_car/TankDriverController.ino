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
		void print(int y, int x );
	public:
		void drive(int x, int y);
		void stop();
		void setup();
		TankDriverController(MotorController _motorLeft, MotorController _motorRight, boolean _singleJoystickMode = true) {
			motorLeft = _motorLeft;
			motorRight = _motorRight;
			singleJoystickMode = _singleJoystickMode;
		}
};

void TankDriverController::setup() {
}


void TankDriverController::drive(int y, int x) {
	stop();
	delay(5);	

	print(y, x);
	
	int speedRight, speedLeft;
	speedLeft = y;
	speedRight = y;
	
		if(x > 30) {
			speedLeft = -25;
			speedRight = 25;
		} else if(x < -30) {
			speedLeft = 25;
			speedRight = -25;
		}
		if(x > 50) {
			speedLeft = -40;
			speedRight = 40;
		} else if(x < -50) {
			speedLeft = 40;
			speedRight = -40;
		}
		if(x > 70) {
			speedLeft = -50;
			speedRight = 50;
		} else if(x < -70) {
			speedLeft = 50;
			speedRight = -100;
		}

  Serial.println();
	
	speedLeft = map(speedLeft, 0, 100, 0, 1024);
	speedRight = map(speedRight, 0, 100, 0, 1024);

	print(speedLeft, speedRight);
	motorLeft.setSpeed(speedLeft);
	motorRight.setSpeed(speedRight);
}

void TankDriverController::stop() {
	motorLeft.stop();
	motorRight.stop();
}

String TankDriverController::calculateDirection(int turn) {
	if(turn >= 0){ return RIGHT;}
	return LEFT;
}

void TankDriverController::print(int y, int x ) {
  Serial.print("result: " );
  Serial.print(y );
  Serial.print(" - " );
  Serial.print(x );
  Serial.print("\t\t");
}
#endif