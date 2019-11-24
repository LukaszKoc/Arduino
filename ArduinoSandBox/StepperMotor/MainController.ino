#include <Pins.ino>

#include <Arduino.h>
#include <SoftwareSerial.h>

#define ENVIRONMENT "arduino"

#include <ArduinoUtilController.ino>
#include <MotorController.ino>
#include <JoyStickController.ino>
#include <SpeedController.ino>

ArduinoUtilController util;
JoyStickController joyStick(JS_X_A_PIN, JS_Y_A_PIN, JS_SW_PIN);
MotorController motorLeftController(MOTOR_2_TURN_1_PIN, MOTOR_2_TURN_2_PIN);
SpeedController speedController(MOTOR_HYALL_1_PIN, MOTOR_HYALL_2_PIN);	
	void setup() {
		Serial.begin(115200);
		joyStick.setup();
		motorLeftController.setup();
		speedController.setup();
		Serial.print("\n\nREDY\n");
	}
	int x, y, z;
	void loop() {
		speedController.doRead();
		readJoystick(x, y, z);
		if(x < 0) {
			x = 0;
		}
		motorLeftController.setSpeed(x);
		// util.endLoop();
	}

	void readJoystick(int &x, int &y, int &z) {
		y = joyStick.readY();
		x = joyStick.readX();
		z = joyStick.readS();
	}

	void display(int x, int y, int z = -1) {
		Serial.print(x);
		Serial.print(";\t");
		Serial.print(y);
		if(z != -1) {
			Serial.print(";\t");
			Serial.print(z);
		}
	}

	void displayPins(){
		Serial.println();
		Serial.print("\t");
		Serial.print("MOTOR_HYALL_2_PIN\n");
		Serial.print(digitalRead(MOTOR_HYALL_1_PIN));
		Serial.print("\t");
		Serial.print("MOTOR_HYALL_1_PIN\n");
		Serial.print(digitalRead(MOTOR_HYALL_2_PIN));
	}
