
/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <Arduino.h>
#include <SoftwareSerial.h>

#include "Pins.ino"
#include "ArduinoUtilController.ino"
#include "WifiConnector.ino"
#include "MotorController.ino"
#include "SpeedController.ino"
#include "TankDriverController.ino"
#include "R2D2Controller.ino"

ArduinoUtilController util;
MotorController motorLeftController(MOTOR_L_TURN_1_PIN, MOTOR_L_TURN_2_PIN);
MotorController motorRightController(MOTOR_R_TURN_1_PIN, MOTOR_R_TURN_2_PIN);

SpeedController speedController(MOTOR_R_HYALL_1_PIN, MOTOR_R_HYALL_2_PIN);

TankDriverController tankDriver(motorLeftController,motorRightController);
R2D2Controller r2D2Controller(R2D2_BUZZER);

// Trojdena
char* ssid     = "UPCCF2D79F";
char* password = "N2nrcsz2fxbb";
// Replace with your network credentials
//Stokłosy 
// char* ssid     = "UPCB3F388D";
// char* password = "Phh4m2beyvGe";
//telefon 
// char* ssid     = "use the route luke";
// char* password = "01234567";

int x, y;
int tillStop = 1;

#import "index.h"
String setResponseHtmlDoc() {
  String s = javascriptCode;
  return s;
}
WifiConnector wifiConnector( setResponseHtmlDoc() );

void setup() {
  Serial.begin(115200);
  speedController.setup();
  r2D2Controller.setup();
  motorLeftController.setup();
  motorRightController.setup();
  tankDriver.stop();
  tankDriver.setup();
  int a0 = analogRead(ACCESS_POINT_PINT);
  Serial.print("\nACCESS_POINT_PINT: ");
  Serial.println(a0);
  if(a0 > 500) {
    wifiConnector.openAccessPoint();
  } else {
    wifiConnector.connect(ssid, password);
  }
  r2D2Controller.r2D2_tell();
}

String midString(String str, String start, String finish) {
  int locStart = str.indexOf(start);
  if (locStart == -1) return "";
  locStart += start.length();
  int locFinish = str.indexOf(finish, locStart);
  if (locFinish == -1) return "";
  return str.substring(locStart, locFinish);
}

void requestCallback(String header) {
  x = midString(header, "x=", "&").toInt();
  y = midString(header, "y=", " ").toInt();
}

void loop() {
  wifiConnector.activate();
  String headerData = wifiConnector.getRequest();
  if(headerData != NULL && headerData.indexOf("joystickCoords") != -1) {
    requestCallback(headerData);
    float speedL = speedController.getSpeedL();
    wifiConnector.setSpeedLeft(speedL);
    // Serial.println(speedL);
    tankDriver.drive(y, x);
  }
  util.endLoop(0);
}