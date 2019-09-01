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
#include <JoyStickController.ino>
#include <MotorController.ino>


Constants constants;
IRController iRController;
DisplayController displayController;
JoyStickController joyStick(JS_X_A_PIN, JS_Y_A_PIN, JS_SW_PIN);
ServoController servoController(SERVO_INPUT);
MotorController motor1Controller(MOTOR_1_SPREED_A_PIN, MOTOR_1_TURN_1_PIN, MOTOR_1_TURN_2_PIN);
MotorController motor2Controller(MOTOR_2_SPREED_A_PIN, MOTOR_2_TURN_1_PIN, MOTOR_2_TURN_2_PIN);

void setup() {
	 Serial.begin(115200);
	// iRController.setup();
	// displayController.setup();
	// servoController.setup();
	joyStick.setup();
	motor1Controller.setup();
	motor2Controller.setup();
	Serial.print("\n\nREDY\n");
}

void loop() {
	int x, y, s;
	x = joyStick.readX();
  	y = joyStick.readY();
	x = x-500;
  	y = y-500;
  	x = x/2;
	y = y/2;
	    Serial.print("\n");
		Serial.print(" X:");
		Serial.print(x);
		Serial.print(" \tY:");
		Serial.print(y);
	motor1Controller.setSpeed(x);
	motor2Controller.setSpeed(y);
	
		delay(100);
	// int x, y, s;
	
	// s = joyStick.readS();
	// 	Serial.print("S:");
	// 	Serial.print(s);
	// 	Serial.print("; \tX:");
	// 	Serial.print(x);
	// 	Serial.print("; \tY:");
	// 	Serial.print(y);
	// 	Serial.print("\n");
	// 	servoController.moveToPosition(x/4);	
}
