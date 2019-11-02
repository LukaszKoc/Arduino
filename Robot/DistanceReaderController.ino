#ifndef DistanceReaderController_h
#define DistanceReaderController_h 

#define HC_RC_ROUNDTRIP_CM 58

class DistanceReaderController {
	private:
		int triggerPin, echoPin;
	public:
		int readDistance();
		void setup();
		DistanceReaderController(int triggerPin_arg, int echoPin_arg) {
			triggerPin = triggerPin_arg;
			echoPin = echoPin_arg;	
		}
}; 

void  DistanceReaderController::setup() {
	pinMode(triggerPin, OUTPUT); //Konfiguracja pinu 13 jako wyjście
	pinMode(echoPin, INPUT); //Konfiguracja pinu 13 jako wyjście

}

int DistanceReaderController::readDistance() {
	long czas, dystans;
	digitalWrite(triggerPin, LOW);
	delayMicroseconds(2);
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);

	return pulseIn(echoPin, HIGH) / HC_RC_ROUNDTRIP_CM;
}
#endif