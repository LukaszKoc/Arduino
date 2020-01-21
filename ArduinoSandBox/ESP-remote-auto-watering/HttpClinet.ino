#ifdef ESP32
	#include <WiFi.h>
	#include <HTTPClient.h>	
	#include <WiFiMulti.h>
	#include <DHT.h>
#elif defined(ESP8266)
	#include <ESP8266WiFi.h>
	#include <ESP8266HTTPClient.h>
	#include <DHTesp.h>
#else
	#error Platform not supported
#endif

#include <ArduinoUtil.h>
#include <PinsESP.h>
#include <WifiConnector.h>
#include <ArduinoJson.h>

WiFiMulti wifiMulti;
HTTPClient http;
DHT dht(DHT_PIN_D, DHT11);


String adresses[][4] = {
//{nettName, pass}
 {"UPCCF2D79F", "N2nrcsz2fxbb"},  // Trojdena
 {"UPCB3F388D", "Phhe4m2beyvGe"}, //stokłosy
 {"FEROmedia_13907", "BorysBestia00"},  //przywory
 {"use the route luke", "01234567"}, //telefon
};

IPAddress staticIps[][4] = {
//{gateway, subnet, staticIP}
 {IPAddress(192, 168, 0, 1), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 1, 170)},	//Trojdena
 {IPAddress(192, 168, 0, 100), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 1, 170)},//stokłosy
 {IPAddress(192, 168, 1, 100), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 1, 141)},//przywory
 {IPAddress(192, 168, 43, 1), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 43, 140)},//telefon
};

// String http_host = "192.168.0.169:8080";
String http_host = "home-master-server.herokuapp.com";
String http_uri = "/api/sensor/recordsPack";
String http_url ="http://"+ http_host + http_uri;


StaticJsonDocument<JSON_ARRAY_SIZE(64)> doc;

JsonArray jsonArrayPopulate (JsonArray array, String field1, int value1, String field2, String value2) {
  JsonObject object = array.createNestedObject();
  object[field1] = value1;
  object[field2] = value2;
  return array;
}

JsonArray jsonArray () {
  return doc.to<JsonArray>();
}

String jsonArraySerialize () {
  String output = "";
  serializeJson(doc, output);
  return output;
}

void setup() {
	Serial.begin(115200);
	WiFi.mode(WIFI_STA);
	wifiMulti.addAP(adresses[0][0].c_str(), adresses[0][1].c_str());
	gpio_set_direction(BLUE_LED_D, GPIO_MODE_OUTPUT);
	gpio_set_pull_mode(BLUE_LED_D, GPIO_PULLUP_ONLY);
	gpio_set_level(BLUE_LED_D, HIGH);
	Serial.print("Waiting for WiFi to connect...");
	while ((wifiMulti.run() != WL_CONNECTED)) {
		Serial.print(".");
	}
	Serial.println(" connected");
	dht.begin();
}

void loop() {   
  	WiFiClient *client = new WiFiClient;

  	if (http.begin(*client, http_url)) {
		http.addHeader("Content-Type", "application/json");
		String msg = getResourcesReprtJsonMsg();
		
		int httpCode = http.POST(msg); 
		String payload = http.getString(); 
		http.end();

		Serial.println(String(" Code: ") + httpCode + ": " + payload); 
		Serial.println(msg);
		if(httpCode == 200) {
			Serial.println("Deep sleap mode.");
			deepSleep(60 * 30);
		}
	}
	delete client;
	wait(1000);
}

String getResourcesReprtJsonMsg() {
	int soilMoistureALOES = 4095 - analogRead(SOID_MOISTURE_A_ALOES);
	int soilMoistureMINT = 4095 - analogRead(SOID_MOISTURE_A_MINT);
	int soilMoistureBURO = 4095 - analogRead(SOID_MOISTURE_A_BURO);
	int soilMoisturePLANT1 = 4095 - analogRead(SOID_MOISTURE_A_PLANT_1);
	int soilMoisturePLANT2 = 4095 - analogRead(SOID_MOISTURE_A_PLANT_1);
	int airTemperature = dht.readTemperature();
	int airHumidity = dht.readHumidity();
	int computeHeatIndex = dht.computeHeatIndex(airTemperature, airHumidity, false);
	JsonArray array = jsonArray(); 
	array = jsonArrayPopulate(array, "sensor", 1, "value", String(soilMoistureALOES));
	array = jsonArrayPopulate(array, "sensor", 2, "value", String(soilMoistureMINT));
	array = jsonArrayPopulate(array, "sensor", 3, "value", String(soilMoistureBURO));
	array = jsonArrayPopulate(array, "sensor", 7, "value", String(soilMoisturePLANT1));
	array = jsonArrayPopulate(array, "sensor", 8, "value", String(soilMoisturePLANT2));

	array = jsonArrayPopulate(array, "sensor", 4, "value", String(airTemperature));
	array = jsonArrayPopulate(array, "sensor", 5, "value", String(airHumidity));
	array = jsonArrayPopulate(array, "sensor", 6, "value", String(computeHeatIndex));
	return jsonArraySerialize();
}