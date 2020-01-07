
#include <Arduino.h>

#include <PinsArduino.h>
#include <SerialLink.h>
#include <SpeedControl.h>
#include <SoundsGenerator.h>

#define BAUD_RATE 9600

SpeedControl speedControl(MOTOR_L_HYALL_1_PIN, MOTOR_L_HYALL_2_PIN, MOTOR_R_HYALL_1_PIN, MOTOR_R_HYALL_2_PIN);
SoundsGenerator soundsGenerator(AR2D2_BUZZER);
SerialLink serialLink;
String msg;

int x, y, speedL, speedR;

void setup() {
	Serial.begin(115200);
	while (!Serial) ;
    serialLink.setup();
	// speedControl.setup();
	// randomSeed(analogRead(RANDOM_GENERATOR_PIN));
 	// soundsGenerator.r2D2_tell();
	Serial.println("READY");
}

void loop() {
	serialLink.write("test 123");
	msg = serialLink.read();
  if(!msg != "-1" && msg != "null") {
		Serial.println();
		Serial.println(msg);
	} else {
		Serial.print('.');
	}
	// String msg = serialLink.read();
	// if( msg != "-1")
	// 	Serial.println();
	// serialLink.read(x, y); Serial.println(String(x) + ": " + y);
	// serialLink.write(speedControl.getSpeedL(), speedControl.getSpeedR());
   // doSaySomething();
   delay(250);
}

void doSaySomething() {
	if(speedL == 0.00 || speedR == 0.00 )
		if(random(100) < 10)
			soundsGenerator.r2D2_tell();
}