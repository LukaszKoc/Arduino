#include <WiFi.h>
#include <WifiConnector.ino>
const char responceHtml [] PROGMEM = "#include 'index.html'";
char* ssid		 = "REPLACE_WITH_YOUR_SSID";
char* password = "REPLACE_WITH_YOUR_PASSWORD";
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
  requestCallback(wifiConnector.getHeader());
  wifiConnector.doResponce();
}

String setResponseHtmlDoc() {
  return responceHtml;
}

void requestCallback(String header) {
  if (header.indexOf("GET /5/on") >= 0) {
    Serial.println("GPIO 5 on");
    output5State = "on";
    digitalWrite(output5, HIGH);
  } else if (header.indexOf("GET /5/off") >= 0) {
    Serial.println("GPIO 5 off");
    output5State = "off";
    digitalWrite(output5, LOW);
  } else if (header.indexOf("GET /4/on") >= 0) {
    Serial.println("GPIO 4 on");
    output4State = "on";
    digitalWrite(output4, HIGH);
  } else if (header.indexOf("GET /4/off") >= 0) {
    Serial.println("GPIO 4 off");
    output4State = "off";
    digitalWrite(output4, LOW);
  }
}
