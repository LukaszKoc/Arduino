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
MotorController motorLeftController( MOTOR_2_TURN_1_PIN, MOTOR_2_TURN_2_PIN);
MotorController motorRightController( MOTOR_1_TURN_1_PIN, MOTOR_1_TURN_2_PIN);
TankDriverController tankDriver(motorLeftController,motorRightController);


// Replace with your network credentials
char* ssid     = "UPCCF2D79F";
char* password = "N2nrcsz2fxbb";
int x, y, oldX, oldY;

#import "index.h"
WifiConnector wifiConnector( setResponseHtmlDoc() );

void setup() {
  digitalWrite(MOTOR_1_SPREED_A_PIN, HIGH);
  digitalWrite(MOTOR_2_SPREED_A_PIN, HIGH);
  Serial.begin(115200);
  wifiConnector.connect(ssid, password);
  tankDriver.drive(0, 0);
}

void loop() {
  wifiConnector.activate();
  String headerData = wifiConnector.getRequest();

  if (headerData != NULL && headerData.indexOf("joystickCoords") != -1) {
        requestCallback(headerData);
       x = map(x, 0, 100, 0, 1024);
       y = map(y, 0, 100, 0, 1024);
    }
    tankDriver.drive(x, y);
    oldX = x;
    oldY = y;
    util.endLoop(500);
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
  Serial.print(" - " );
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

