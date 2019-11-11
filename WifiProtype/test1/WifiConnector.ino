#ifndef WifiConnector_h
#define WifiConnector_h 

WiFiServer server(80);

class WifiConnector {
	private:
		int httpCode;
		String header;
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
		String getHeader();
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
	client = server.available();	 // Listen for incoming clients
	header = "";
	if (client) {										// If a new client connects,
		// Serial.println("New Client.");					// print a message out in the serial port
		String currentLine = "";								// make a String to hold incoming data from the client
		currentTime = millis();
		previousTime = currentTime;
		while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
			currentTime = millis();				 
			if (client.available()) {						 // if there's bytes to read from the client,
				char c = client.read();						 // read a byte, then
				// Serial.write(c);										// print it out the serial monitor
				header += c;
				if (c == '\n') {										// if the byte is a newline character
					if (currentLine.length() == 0) {
						if (header.indexOf("GET") >= 0) {
		  					doResponce();					
						} else {
							doResponce(200);
						}
						break;
					} else { // if you got a newline, then clear currentLine
						currentLine = "";
					}
				} else if (c != '\r') {	// if you got anything else but a carriage return character,
					currentLine += c;			// add it to the end of the currentLine
				}
			}
		}
	}
}

void  WifiConnector::doResponce() {
	if (client) {
		client.println(getResponseStatus(httpCode));  
		client.println(responseDoc); 
		client.stop();
	}
}

void  WifiConnector::doResponce(int status) {
	if (client) {
		client.println(getResponseStatus(status));  
		client.stop();
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

String WifiConnector::getHeader() {
	return header;
}

String WifiConnector::getPath() {
	return path;}
#endif