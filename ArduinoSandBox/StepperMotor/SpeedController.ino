#ifndef SpeedController_h
#define SpeedController_h 

int pulsesChanged, pulses, encoderA, encoderB;
class SpeedController {
	private:
		int interruptPin, last, maxSpeed;
		int read();
		static void redSencores();
	public:
		void setup();
		void doRead();		
		SpeedController(int sencor1_arg, int sencor2_arg) {
			interruptPin = sencor1_arg;
			encoderA = sencor1_arg; 
			encoderB = sencor2_arg;
		}
}; 

void SpeedController::setup() {
  pinMode(encoderA, INPUT);
  digitalWrite(encoderB, HIGH);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(0, redSencores, CHANGE);
}

void SpeedController::doRead() {
	if (pulsesChanged != 0) {
		pulsesChanged = 0;
		Serial.println(pulses);
	}
}

static void SpeedController::redSencores() {
  if ( digitalRead(encoderB) == 0 ) {
    if ( digitalRead(encoderA) == 0 ) {
      // A fell, B is low
      pulses--; // Moving forward
    } else {
      // A rose, B is high
      pulses++; // Moving reverse
    }
  } else {
    if ( digitalRead(encoderA) == 0 ) {
      pulses++; // Moving reverse
    } else {
      // A rose, B is low
      pulses--; // Moving forward
    }
  }
  pulsesChanged = 1;
}

#endif