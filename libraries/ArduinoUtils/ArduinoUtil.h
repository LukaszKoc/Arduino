#ifndef ArduinoUtil_h
#define ArduinoUtil_h 


void wait(int timeout = 500) {
	delay(timeout);
	Serial.print(".");
}

#endif