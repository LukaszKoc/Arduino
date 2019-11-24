/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <Regexp.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WifiConnector.ino>
#include <Pins.ino>
#include <ArduinoUtilController.ino>
#include <MotorController.ino>
#include <TankDriverController.ino>

ArduinoUtilController util;
MotorController motorLeftController(MOTOR_2_TURN_1_PIN, MOTOR_2_TURN_2_PIN);
MotorController motorRightController(MOTOR_1_TURN_1_PIN, MOTOR_1_TURN_2_PIN);
TankDriverController tankDriver(motorLeftController,motorRightController);

// Replace with your network credentials
char* ssid     = "UPCCF2D79F";
char* password = "N2nrcsz2fxbb";
int x, y;
int tillStop = 1;

#import "index.h"
WifiConnector wifiConnector( setResponseHtmlDoc() );

void setup() {
  Serial.begin(115200);
  motorLeftController.setup();
  motorRightController.setup();
  tankDriver.stop();
  tankDriver.setup();
  wifiConnector.connect(ssid, password);
}

void loop() {
  wifiConnector.activate();
  String headerData = wifiConnector.getRequest();
  if(headerData != NULL && headerData.indexOf("joystickCoords") != -1) {
    requestCallback(headerData);
    tankDriver.drive(y, x);
  }
  util.endLoop(200);
}

String setResponseHtmlDoc() {
  String s = javascriptCode;
  return s;
}

void requestCallback(String header) {
  x = midString(header, "x=", "&").toInt();
  y = midString(header, "y=", " ").toInt();
  Serial.print("result: " );
  Serial.print(y );
  Serial.print("  " );
  Serial.print(y );
  Serial.println();
}


String midString(String str, String start, String finish) {
  int locStart = str.indexOf(start);
  if (locStart==-1) return "";
  locStart += start.length();
  int locFinish = str.indexOf(finish, locStart);
  if (locFinish==-1) return "";
  return str.substring(locStart, locFinish);
}

