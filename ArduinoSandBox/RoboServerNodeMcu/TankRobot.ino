
/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "PinsNodeMCU.h"

#include <SerialLink.h>
#include "ArduinoUtil.h"
#include "WifiConnector.h"
#include "MotorControl.h"
#include "TankDriver.h"
#include "SoundsGenerator.h"

ArduinoUtil util;
MotorControl motorLeftController(MOTOR_L_TURN_1_PIN, MOTOR_L_TURN_2_PIN);
MotorControl motorRightController(MOTOR_R_TURN_1_PIN, MOTOR_R_TURN_2_PIN);

TankDriver tankDriver(motorLeftController,motorRightController);
SerialLink serialLink;
// Trojdena
char* ssid     = "UPCCF2D79F";
char* password = "N2nrcsz2fxbb";
// Replace with your network credentials
//Stokłosy 
// char* ssid     = "UPCB3F388D";
// char* password = "Phhe4m2beyvGe";
//telefon 
// char* ssid     = "use the route luke";
// char* password = "01234567";

int x, y, speedL, speedR;
int tillStop = 1;

#import "index.h"
String setResponseHtmlDoc() {
  String s = javascriptCode;
  return s;
}
WifiConnector wifiConnector( setResponseHtmlDoc() );

void setup() {
  Serial.begin(115200);
  motorLeftController.setup();
  motorRightController.setup();
  tankDriver.stop();
  tankDriver.setup();
  int a0 = analogRead(ACCESS_POINT_PINT);
  if(a0 > 500) {
    wifiConnector.openAccessPoint();
  } else {
    wifiConnector.connect(ssid, password);
  }
}

void loop() {
  wifiConnector.activate();
  String headerData = wifiConnector.getRequest();
  if(headerData != NULL && headerData.indexOf("joystickCoords") != -1) {
    requestCallback(headerData);
    // wifiConnector.setSpeedLeft(speedL);
    String msg = String("DIRESTIONS:")+ x + ";" + y + ".";
    Serial.println(msg);
    tankDriver.drive(y, x);
  }
  util.endLoop(0);
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
