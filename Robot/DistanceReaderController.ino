#include <NewPing.h>

#ifndef DistanceReaderController_h
#define DistanceReaderController_h 

#define MAX_DISTANCE 400
NewPing sonar(BAT_TRIG_PIN, BAT_ECHO_PIN, MAX_DISTANCE);

class DistanceReaderController {
	private:
	public:
		void setup();
		int readDistance();
		DistanceReaderController() {}
}; 

void DistanceReaderController::setup() {
	pinMode(BAT_TRIG_PIN, OUTPUT); //Pin, do którego podłączymy trig jako wyjście
}

int DistanceReaderController::readDistance() {
	unsigned int distance = sonar.ping();
	pinMode(BAT_ECHO_PIN, OUTPUT);
	digitalWrite(BAT_ECHO_PIN, LOW);
	pinMode(BAT_ECHO_PIN, INPUT);

	return  distance / US_ROUNDTRIP_CM;
}
#endif