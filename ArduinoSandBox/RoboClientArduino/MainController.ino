
/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <Arduino.h>

#include <PinsArduino.h>
#include <SerialLink.h>
#include <SpeedControl.h>
#include <SoundsGenerator.h>

SpeedControl speedControl(MOTOR_L_HYALL_1_PIN, MOTOR_L_HYALL_2_PIN, MOTOR_R_HYALL_1_PIN, MOTOR_R_HYALL_2_PIN);
SoundsGenerator soundsGenerator(AR2D2_BUZZER);
SerialLink serialLink;

int x, y, speedL, speedR;

void setup() {
	Serial.begin(115200);
	serialLink.setup(1152000);
	speedControl.setup();
	randomSeed(analogRead(RANDOM_GENERATOR_PIN));
 	soundsGenerator.r2D2_tell();
	Serial.println("READY");
}

void loop() {
	serialLink.readMessage(x, y); 
	serialLink.writeCurrentSpeed(speedControl.getSpeedL(), speedControl.getSpeedR());

	Serial.println( String(serialLink.readMessage()));
    doSaySomething();
}

void doSaySomething() {
	if(speedL == 0.00 || speedR == 0.00 )
		if(random(100) < 10)
			soundsGenerator.r2D2_tell();
}