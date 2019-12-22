
/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <Arduino.h>
#include <SoftwareSerial.h>

#include "ArduinoPins.ino"
#include "SpeedController.ino"
#include "R2D2Controller.ino"
#include "SerialLinkController.ino"

SpeedController speedController(MOTOR_L_HYALL_1_PIN, MOTOR_L_HYALL_2_PIN, MOTOR_R_HYALL_1_PIN, MOTOR_R_HYALL_2_PIN);
R2D2Controller r2D2Controller(AR2D2_BUZZER);
SerialLinkController serialLinkController;

int x, y, speedL, speedR;

void setup() {
	Serial.begin(115200);
	espSerial.begin(1152000);
	speedController.setup();
	randomSeed(analogRead(RANDOM_GENERATOR_PIN));
	while (!Serial) {
		delay(10); // wait for serial port to connect. Needed for Native USB only
	}		
 	espSerial.flush();
 	r2D2Controller.r2D2_tell();
	Serial.println("READY");
}

void loop() {
	serialLinkController.readMessage(x, y); 
	serialLinkController.writeCurrentSpeed(speedController.getSpeedL(), speedController.getSpeedR());

	Serial.println(String(x) + ": " + y);
    doSaySomething();
}

void doSaySomething() {
	if(speedL == 0.00 || speedR == 0.00 )
		if(random(100) < 10)
			r2D2Controller.r2D2_rand();
}