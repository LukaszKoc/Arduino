#ifndef SpeedController_h
#define SpeedController_h 

/**
* distance - total distance driven in cm
* avgSpeed - avg speed in m/s
* currentSpeed = current speed in m/s 
**/


float MilisecPercentimeters;
float currentSpeed, distance, totalTime;
volatile unsigned long previousMillis = 0;
volatile unsigned long milisNow = 0;
int pulsesChanged, pulses, pulsesTotal, encoderA, encoderB;

class SpeedController {
	private:
		int stepsPerMeter;
    float avgSpeed, maxSpeed;
		int read();
		static void redSencores();
	public:
    void setup();
		void setup(int sencor1_arg, int sencor2_arg, int stepsPerMeter_arg = 1200);
		float getSpeed();		
    SpeedController(int sencor1_arg, int sencor2_arg, int stepsPerMeter_arg = 1200) {
      encoderA = sencor1_arg; 
      encoderB = sencor2_arg;
      stepsPerMeter = stepsPerMeter_arg;
    }
    SpeedController() {
    }
}; 

void SpeedController::setup(int sencor1_arg, int sencor2_arg, int stepsPerMeter_arg) {
  pinMode(encoderA, INPUT);
  digitalWrite(encoderB, HIGH);
  pinMode(encoderA, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderA), redSencores, CHANGE);
}

void SpeedController::setup( ) {
 setup(encoderA, encoderB, stepsPerMeter);
}

float SpeedController::getSpeed() {
	if (pulsesChanged != 0) {
		pulsesChanged = 0;
    return currentSpeed;
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
  if( pulses == 12 || pulses == -12)  {
    distance += 0.01;
    milisNow = millis();
    float ten = 10;
    MilisecPercentimeters = (milisNow - previousMillis);
    if(MilisecPercentimeters > 500) {
      Serial.println("reset");
      previousMillis =  millis();
      pulsesTotal += pulses;
      pulses = 0;
      return;
    }
    totalTime += MilisecPercentimeters;
    previousMillis = milisNow;
    currentSpeed = 0.01 /(MilisecPercentimeters/1000);
    Serial.print(pulsesTotal);
    Serial.print("\t\t\t");
    Serial.print(distance);
    Serial.print("\t\t\t");
    Serial.print(totalTime);
    Serial.print(" ms");
    Serial.print("\t\t\t");
    Serial.print(currentSpeed);
    Serial.print(" m/s");
    Serial.println();
    pulsesTotal += pulses;
    pulses = 0;
  }


  pulsesChanged = 1;
}

#endif