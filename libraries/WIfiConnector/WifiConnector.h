#include <ESP8266WiFi.h>

#ifndef WifiConnector_h
#define WifiConnector_h 
#define port 80
WiFiServer server(port);
//TODO create connection List htstName/pass/IPs


class WifiConnector {
	private:
		float speedL, speedR;
		int httpCode, host;
		String req;
		String path;
		String responseDoc;
		unsigned long currentTime = millis();
		unsigned long previousTime = 0; 
		long timeoutTime = 2000;
		String getResponseStatus(int code);
		void configWiFi();
	public:
		WiFiClient client;
		void openAccessPoint();
		bool connect(char* ssid, char* password);
		void connect(char* adresses[][2], IPAddress staticIps[][3]);
		void setup();
		void activate();
		String getRequest();
		String getPath();
		void doResponce();
		void setSpeedLeft(float spped);
		void setSpeedRight(float spped);
		void doResponce(int status);
		WifiConnector(String response_arg, int httpCode_arg, long timeoutTime_arg) {
			responseDoc = response_arg;
			httpCode = httpCode_arg;
			timeoutTime = timeoutTime_arg;
		}
		WifiConnector(String response_arg) {
			responseDoc = response_arg;
			httpCode = 200;
		}
}; 

void WifiConnector::setup() {
}


void WifiConnector::activate() {
	client = server.available();
	if (!client) {
		return;
	}
	//Serial.println("new client");
	while(!client.available()) {
		delay(1);
	}
	// Read the first line of the request
	req = client.readStringUntil('\r');
	//Serial.println();
	//Serial.println(req);
	client.flush();

	if (req.indexOf("GET") != -1) {
		doResponce();					
	} else {
		doResponce(200);
	}
}

void  WifiConnector::doResponce() {
	if (client) {
		client.println(getResponseStatus(httpCode));  
		client.println(responseDoc); 
	}
}

void  WifiConnector::doResponce(int status) {
	if (client) {
		client.println(getResponseStatus(status)); 
		client.print("{"); 
		client.print("speedL:"); 
		client.print(speedL); 
		client.print(", speedR:"); 
		client.print(speedR); 
		client.print("}\n\n"); 
	}
}

String WifiConnector::getResponseStatus(int code) {
	return 	"HTTP/1.1 " + String(code) + " OK\n"+
			"Content-type:text/html\n"+
			"Connection: Keep-Alive\n\n";
}


void WifiConnector::openAccessPoint() {
	//Serial.println("Setting soft-AP ... ");
	WiFi.hostname("robot-wifi");
  	WiFi.mode(WIFI_AP_STA);
	boolean result = 
		// WiFi.softAPConfig(staticIP, gateway, subnet) && 
		WiFi.softAP("ESP_ROBOT");
	if(result == true) {
		//Serial.println("Acces ponit Ready");
	} else {
		//Serial.println("Acces ponit Failed!");
	}
	//Serial.println(WiFi.localIP());
}

void WifiConnector::connect(char* adresses[][2], IPAddress staticIps[][3]) {
	WiFi.mode(WIFI_STA); //WiFi mode station (connect to wifi router only
	for (int i=0; i< sizeof(adresses); i++){
		Serial.println("Connecting: ");Serial.print(adresses[i][0]); 
		if(connect(adresses[i][0], adresses[i][1])){
			WiFi.config(staticIps[i][2], staticIps[i][1], staticIps[i][0]);
			Serial.print("\nIP address: ");
			Serial.println(WiFi.localIP());
			server.begin();
			Serial.println("");
			Serial.println("WiFi connected.");
			return;
		}
	}
}

bool WifiConnector::connect(char* ssid, char* password) {
	WiFi.begin(ssid, password);
	int timeout = millis() + 15000; 
	for ( int i = millis(); millis() < timeout;) {
		wait(250);
		if(WiFi.status() == WL_CONNECTED) { 
			return true;
		}
	}
	return false;
}

String WifiConnector::getRequest() {
	String requestData  = req;
	req = "";
	return requestData;
}

void WifiConnector::setSpeedLeft(float spped) {
	speedL = spped;
}
void WifiConnector::setSpeedRight(float spped) {
	speedR = spped;
}

String WifiConnector::getPath() {
	return path;}
#endif