
#include <WiFi.h>
#include <HTTPClient.h>	
#include <WiFiMulti.h>
#include <DHT.h>

#include <ArduinoUtil.h>
#include <PinsESP.h>
#include <WifiConnector.h>
#include <LinkedList.h>

WiFiMulti wifiMulti;
HTTPClient http;
DHT dht(DHT_PIN_D, DHT11);


String adresses[][4] = {
//{nettName, pass}
 {"UPCB3F388D", "Phhe4m2beyvGe"}, //stokłosy
 {"UPCCF2D79F", "N2nrcsz2fxbb"},  // Trojdena
 {"FEROmedia_13907", "BorysBestia00"},  //przywory
 {"use the route luke", "01234567"}, //telefon
};

IPAddress staticIps[][4] = {
//{gateway, subnet, staticIP}
 {IPAddress(192, 168, 0, 1), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 1, 121)},	//Trojdena
 {IPAddress(192, 168, 0, 100), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 1, 121)},//stokłosy
 {IPAddress(192, 168, 1, 100), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 1, 121)},//przywory
 {IPAddress(192, 168, 43, 1), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 43, 121)},//telefon
};

String serverIp = "89.70.154.199:9080";
String domoticzServerUrl = String("http://") + serverIp + "/json.htm";

class Sensor {
	private:
		int pin, uId, maxValue;
	public:
		int getPin() {return pin;};
		int getUId() {return uId;};
		int getMaxValue() {return maxValue;};
		Sensor(int _pin, int _uId, int _maxValue) {
			pin = _pin;
			uId = _uId;
			maxValue = _maxValue;
		}
};

LinkedList<Sensor*> myAnimalList = LinkedList<Sensor*>();

void setup() {
    Serial.begin(115200);
	pinMode(POWER_D, OUTPUT);
	digitalWrite(POWER_D, HIGH);
    myAnimalList.add(new Sensor(SOID_MOISTURE_A_BURO, 1, 200));
    myAnimalList.add(new Sensor(SOID_MOISTURE_A_MINT, 2, 200));
    myAnimalList.add(new Sensor(SOID_MOISTURE_A_ALOES, 3, 200));
    myAnimalList.add(new Sensor(SOID_MOISTURE_A_PLANT_1, 4, 200));
    myAnimalList.add(new Sensor(SOID_MOISTURE_A_PLANT_2, 5, 200));
	WiFi.mode(WIFI_STA);
	Serial.print("Waiting for WiFi to connect...");
	wifiMulti.addAP(adresses[0][0].c_str(), adresses[0][1].c_str());
	wifiMulti.addAP(adresses[1][0].c_str(), adresses[1][1].c_str());
	while((wifiMulti.run() != WL_CONNECTED)) {
		Serial.print(".");
		delay(50);
	}
	dht.begin();
    Serial.printf(" connected to %s\n", WiFi.SSID().c_str());
}

void loop() {   
  	WiFiClient *client = new WiFiClient;
    Sensor *sensor;
    sendDHTData(client, 6);
    for(int i = 0; i<myAnimalList.size() && myAnimalList.get(i) -> getPin() != NULL; i++) {
		sensor = myAnimalList.get(i);
		int value = 4095 - analogRead(sensor->getPin());
		if(value < 4000) {
			value  = map(value, 0, 4095, 0, sensor->getMaxValue());
			String url = getSensorDestinationURL(sensor->getUId(), value);
			if(200 == sendSensorData(client, url)) {
				myAnimalList.remove(i);
			}
		} 
    }

	if(myAnimalList.size() == 0) {
		uint64_t deepSleepMin = 30;
		Serial.println("Deep sleap mode: ");
		deepSleep(60 * deepSleepMin);
	}
	
	delete client;
	wait(10);
}

int sendDHTData(WiFiClient *client, int sensorId) {
	int airTemperature = dht.readTemperature();
	int airHumidity = dht.readHumidity();
	int airHumidityStatus = 0;

	if(airHumidity > 45 && airHumidity < 50) {
		airHumidityStatus = 1;
	} else if(airHumidity > 70) {
		airHumidityStatus = 3;
	}else if(airHumidity > 30) {
		airHumidityStatus = 2;
	}

    String sensorPrefix = String("?type=command&param=udevice&idx=") + sensorId + "&nvalue=0";
    String sensorDataParam = String("&svalue=") + airTemperature + ";" + airHumidity + ";" + airHumidityStatus;

    return sendSensorData(client, domoticzServerUrl + sensorPrefix + sensorDataParam);

}

int sendSensorData(WiFiClient *client, String url) {
 if (http.begin(*client, url)) {
		http.addHeader("Content-Type", "application/json");
		int httpCode = http.GET();
		Serial.println(String("Sent: ") + httpCode + ":"+ url );
		http.end();
        return httpCode;
	}
	return -11;
}


String getSensorDestinationURL(int sensorId, int value) {
    String sensorPrefix = String("?type=command&param=udevice&idx=") + sensorId;
    String sensorDataParam = String("&nvalue=") + value;

    return domoticzServerUrl + sensorPrefix + sensorDataParam;
}

