#include <Pins.ino>
#include <SoftwareSerial.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#include <DisplayController.ino>
#include <IRController.ino>
#include <Constants.ino>
#include <ServoController.ino>
#include <InputXYS.ino>
#include <JoyStickController.ino>

IRController iRController;
DisplayController displayController;
Constants constants;
JoyStickController joyStick;
ServoController servoController;


void setup() {
	Serial.begin(115200);
	constants.setup();
	iRController.setup();
	displayController.setup();
	joyStick.setup();
	servoController.setup();
	Serial.print("\n\nREDY\n");
}

void loop() {
	int x, y, s;

	x = joyStick.readX();
 	y = joyStick.readY();
	s = joyStick.readS();
		Serial.print("S:");
		Serial.print(s);
		Serial.print("; \tX:");
		Serial.print(x);
		Serial.print("; \tY:");
		Serial.print(y);
		Serial.print("\n");
		servoController.moveToPosition(x/4);	
		delay(100);
}
