
#include <Arduino.h>
#include <SoftwareSerial.h>

#define RX_PIN 3
#define TX_PIN 2

String str;
SoftwareSerial espSerial(RX_PIN, TX_PIN);

void setup() {
	Serial.begin(1152000);
	espSerial.begin(115200);
	while (!Serial) {
		delay(10); // wait for serial port to connect. Needed for Native USB only
	}		
 	espSerial.flush();
	Serial.println(" READY");
}

void loop()
{
	String msg = espSerial.readString();
    Serial.print(msg);
}