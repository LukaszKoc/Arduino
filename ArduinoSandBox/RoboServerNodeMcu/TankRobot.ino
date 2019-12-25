
/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#define DC_FREQUENCY 400720
#define DC_RANGE 10240
// Load Wi-Fi library
#include "PinsNodeMCU.h"

#include <SerialLinkESP.h>
#include "WifiConnector.h"
#include "MotorControl.h"
#include "TankDriver.h"

MotorControl motorLeftController(MOTOR_L_TURN_1_PIN, MOTOR_L_TURN_2_PIN);
MotorControl motorRightController(MOTOR_R_TURN_1_PIN, MOTOR_R_TURN_2_PIN);
TankDriver tankDriver(motorLeftController,motorRightController);
SerialLink serialLink;

#import "index.h"
String setResponseHtmlDoc() {
  return String(javascriptCode);
}

WifiConnector wifiConnector( setResponseHtmlDoc() );

char* ssid     = "FEROmedia_13907";
char* password = "BorysBestia00";
char* adresses[][2] = {
  {"FEROmedia_13907", "BorysBestia00"},// Przywory
  {"UPCCF2D79F", "N2nrcsz2fxbb"}, //trojdena
  {"UPCB3F388D", "Phhe4m2beyvGe"},
  {"use the route luke", "01234567"}
};

int x, y, speedL, speedR;
int tillStop = 1;


void setup() {
  Serial.begin(115200);
  Serial.println("ESP setup:");

  motorLeftController.setup();
  motorRightController.setup();
  int a0 = analogRead(ACCESS_POINT_PINT);
  if(a0 > 500) {
    wifiConnector.openAccessPoint();
  } else {
    wifiConnector.connect(adresses[1][0], adresses[1][1]);
  }
  // serialLink.setup();
  Serial.println("ESP ready:");
}

void loop() {
  wifiConnector.activate();
  String headerData = wifiConnector.getRequest();
  if(headerData != NULL && headerData.indexOf("joystickCoords") != -1) {
    requestCallback(headerData);
    // String msg = String("DIRESTIONS:") + x + ";" + y + ".";
    // Serial.println(msg);
    // wifiConnector.setSpeed(speedL, speedR);
    tankDriver.drive(y, x);
  }
   
  // String msg = String(serialLink.read());
  // if(msg != "-1" && msg != "null") {
  //   serialLink.write("ACK: " + msg);
  // }
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
