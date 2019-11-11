/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <Regexp.h>
#include <WifiConnector.ino>

// Replace with your network credentials
char* ssid     = "UPCCF2D79F";
char* password = "N2nrcsz2fxbb";

// Set web server port number to 80
#import "index.h"
// const char responceHtml [] PROGMEM = "#include 'index.html'";
String output5State = "off";
String output4State = "off";
const int output5 = 5;
const int output4 = 4;

WifiConnector wifiConnector(setResponseHtmlDoc());

void setup() {
  Serial.begin(115200);
	// Initialize the output variables as outputs
	pinMode(output5, OUTPUT);
	pinMode(output4, OUTPUT);
	// Set outputs to LOW
	digitalWrite(output5, LOW);
	digitalWrite(output4, LOW);
	// Connect to Wi-Fi network with SSID and password
  wifiConnector.connect(ssid, password);
}

void loop(){
  wifiConnector.activate();
  String headerData = wifiConnector.getHeader();

  if (headerData != NULL ) {
    headerData = midString(headerData, "joystickCoords", "\n");
    requestCallback(headerData);
    wifiConnector.doResponce(200);
  }
}

String setResponseHtmlDoc() {
  String s = javascriptCode;
  return s;
}

void requestCallback(String header) {
    Serial.println("header: ");
    Serial.println( header);

    int x = midString(header, "x=", "&").toInt();
    int y = midString(header, "y=", " ").toInt();
    Serial.print("result: " );
    Serial.print(y );
    Serial.print(" - " );
    Serial.print(y );
    Serial.println();
  }

String midString(String str, String start, String finish){
  int locStart = str.indexOf(start);
  if (locStart==-1) return "";
  locStart += start.length();
  int locFinish = str.indexOf(finish, locStart);
  if (locFinish==-1) return "";
  return str.substring(locStart, locFinish);
}
