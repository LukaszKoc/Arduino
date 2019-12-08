#ifndef SpeedController_h
#define SpeedController_h 

/**
* distance - total distance driven in cm
* avgSpeed - avg speed in m/s
* currentSpeed = current speed in m/s 
**/

float milisecPerCentimeter = 0.0;
float currentSpeedL = 0.0;
long previousMillisL = 0.0;
long milisNowL = 0.0;
int pulsesChanged, pulsesL, encoderAL, encoderBL;

const int stepsPerCentyMeter = 12;
void ICACHE_RAM_ATTR readSpeedLeft();
void redSencores(int encoderA, int encoderB, int &pulses);
float calculateSpeed(int &pulses, long &milisNow, long &previousMillis);

class SpeedController {
	private:
		int read();
	public:
    void setup();
		void setup(int sencor1_arg, int sencor2_arg);
    SpeedController() { }
    SpeedController(int sencor1_arg, int sencor2_arg) {
      encoderAL = sencor1_arg; 
      encoderBL = sencor2_arg;
    }
		float getSpeedL();		
}; 

void SpeedController::setup(int sencor1_arg, int sencor2_arg) {
  digitalWrite(encoderAL, HIGH);
  digitalWrite(encoderAL, HIGH);
  pinMode(encoderAL, INPUT_PULLUP);
  pinMode(encoderBL, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderAL), readSpeedLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderBL), readSpeedLeft, CHANGE);
}

void SpeedController::setup( ) {
  setup(encoderAL, encoderBL);
}

float SpeedController::getSpeedL() {
	if (pulsesChanged != 0) {
		pulsesChanged = 0;
    return currentSpeedL;
	}
}

void readSpeedLeft() {
  Serial.print("interrupt: ");
  redSencores(encoderAL, encoderBL, pulsesL);
  currentSpeedL = calculateSpeed(pulsesL, milisNowL, previousMillisL);
  Serial.print(pulsesL);
  Serial.print("\t\t");
  Serial.println(currentSpeedL);
}

void redSencores(int encoderA, int encoderB, int &pulses) {
  Serial.print("\tA: ");
  Serial.print(digitalRead(encoderA));
  Serial.print("\tB: ");
  Serial.print(digitalRead(encoderB));
  Serial.print("\t");

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

float calculateSpeed(int &pulses, long &milisNow, long &previousMillis) {
  float currentSpeed = 0;
  if( pulses == stepsPerCentyMeter || pulses == -stepsPerCentyMeter) {
    milisNow = millis();
    milisecPerCentimeter = (milisNow - previousMillis);
    if(milisecPerCentimeter > 500) {
      previousMillis =  milisNow;
      pulses = 0;
      return -1;
    }
    previousMillis = milisNow;
    currentSpeed = 0.01 /(milisecPerCentimeter/1000);
    pulses = 0;
  }
  return currentSpeed;
}

#endif