#include <Pins.ino>
#include <Arduino.h>
#include <SoftwareSerial.h>

#include <ArduinoUtilController.ino>
#include <MotorController.ino>
#include <JoyStickController.ino>
#include <CarController.ino>
#include <TankDriverController.ino>
#include <DistanceReaderController.ino>

ArduinoUtilController util;
JoyStickController joyStick(JS_X_A_PIN, JS_Y_A_PIN, JS_SW_PIN);
MotorController motorLeftController(MOTOR_2_SPREED_A_PIN, MOTOR_2_TURN_1_PIN, MOTOR_2_TURN_2_PIN);
MotorController motorRightController(MOTOR_1_SPREED_A_PIN, MOTOR_1_TURN_1_PIN, MOTOR_1_TURN_2_PIN);
CarController carController(motorLeftController,motorRightController);
TankDriverController tankDriver(motorLeftController,motorRightController);
DistanceReaderController bat;

	void setup() {
		Serial.begin(115200);
		Serial.print("\n\nREDY\n");
	}

	void loop() {
		Serial.println(bat.readDistance());
		util.endLoop(200);
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
		Serial.print("\n");
		Serial.print(digitalRead(MOTOR_1_TURN_1_PIN));
		Serial.print("\t");
		Serial.print("MOTOR_1_TURN_1_PIN\n");
		Serial.print(digitalRead(MOTOR_1_TURN_2_PIN));
		Serial.print("\t");
		Serial.print("MOTOR_1_TURN_2_PIN\n");
		Serial.print(analogRead(MOTOR_1_SPREED_A_PIN));
		Serial.print("\t");
		Serial.print("MOTOR_1_SPREED_A_PIN\n\n");

		Serial.print(digitalRead(MOTOR_2_TURN_1_PIN));
		Serial.print("\t");
		Serial.print("MOTOR_2_TURN_1_PIN\n");
		Serial.print(digitalRead(MOTOR_2_TURN_2_PIN));
		Serial.print("\t");
		Serial.print("MOTOR_2_TURN_2_PIN\n");
		Serial.print(analogRead(MOTOR_2_SPREED_A_PIN));
		Serial.print("\t");
		Serial.print("MOTOR_2_SPREED_A_PIN\n");
	}
