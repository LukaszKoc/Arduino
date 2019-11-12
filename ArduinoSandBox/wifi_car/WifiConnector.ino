#ifndef WifiConnector_h
#define WifiConnector_h 
#define port 80
WiFiServer server(port);

class WifiConnector {
	private:
		int httpCode, host;
		String req;
		String path;
		String responseDoc;
		unsigned long currentTime = millis();
		unsigned long previousTime = 0; 
		long timeoutTime = 2000;
		String getResponseStatus(int code);
	public:
		WiFiClient client;
		void connect(char* ssid, char* password);
		void setup();
		void activate();
		String getRequest();
		String getPath();
		void doResponce();
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
	Serial.println("new client");
	while(!client.available()) {
		delay(1);
	}
	// Read the first line of the request
	req = client.readStringUntil('\r');
	Serial.println();
	Serial.println(req);
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
	}
}


String WifiConnector::getResponseStatus(int code) {
	return 	"HTTP/1.1 " + String(code) + " OK\n"+
			"Content-type:text/html\n"+
			"Connection: Keep-Alive\n\n";
}


void WifiConnector::connect(char* ssid, char* password) {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

String WifiConnector::getRequest() {
	String requestData  = req;
	req = "";
	return requestData;
}

String WifiConnector::getPath() {
	return path;}
#endif