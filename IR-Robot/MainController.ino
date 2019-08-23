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

InputXYS joyInput;

void setup() {
	Serial.begin(9600);
}

void loop() {
	joyInput.setX(1);
	joyInput.setY(2), 
	joyInput.setS(3);
	Serial.print("X= " + joyInput.getX());
	Serial.print("Y= " + joyInput.getY());
	Serial.print("S= " + joyInput.getS());
	joyInput.setX(4);
	joyInput.setY(5), 
	joyInput.setS(6);
	Serial.print("X= " + joyInput.getX());
	Serial.print("Y= " + joyInput.getY());
	Serial.print("S= " + joyInput.getS());

	joyStick.readInput(&joyInput);
	String inputCommand = constants.mapIRCode(iRController.readIRInputCode());
}
