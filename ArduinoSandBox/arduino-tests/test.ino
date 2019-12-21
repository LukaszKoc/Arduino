
#include <Arduino.h>
#include <SoftwareSerial.h>

#include "PinsArduino.ino"
#include "R2D2Controller.ino"

R2D2Controller r2D2Controller(AR2D2_BUZZER);
void setup() {
	Serial.begin(115200);
	r2D2Controller.setup();
	r2D2Controller.r2D2_rand();	
}

void loop() {
	delay(500);

	r2D2Controller.r2D2_rand();	
}