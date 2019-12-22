#ifndef DistnceReaderController_h
#define DistnceReaderController_h 

class DistnceReaderController {
	private:
		int trigPin, echoPin;
	public:
		void setup();
		int readDistance();
		int off();
		DistnceReaderController(int trigPin_arg, int echoPin_arg) {
			trigPin = trigPin_arg; 
			echoPin = echoPin_arg;
		}
}; 

void DistnceReaderController::setup() {
	pinMode(trigPin, OUTPUT); //Pin, do którego podłączymy trig jako wyjście
	pinMode(echoPin, INPUT); //a echo, jako wejście
}

int DistnceReaderController::readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long time = pulseIn(echoPin, HIGH);
  return time / 58;
}


int DistnceReaderController::off() {
  digitalWrite(trigPin, LOW);
}

#endif