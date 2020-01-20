#include <ArduinoUtil.h>
#include <ESP8266HTTPClient.h>
#include <WifiConnector.h>
#include <DHTesp.h>
#include <ArduinoJson.h>

#define DHT11_PIN D6
#define DHTTYPE DHTesp::DHT11 

HTTPClient http;
DHTesp dht;
WifiConnector wifiConnector("");

char* adresses[][2] = {
//{nettName, pass}
 {"FEROmedia_13907", "BorysBestia00"},  //przywory
 {"use the route luke", "01234567"}, //telefon
 {"UPCCF2D79F", "N2nrcsz2fxbb"},  // Trojdena
 {"UPCB3F388D", "Phhe4m2beyvGe"},
};
IPAddress staticIps[][3] = {
//{gateway, subnet, staticIP}
 {IPAddress(192, 168, 1, 100), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 1, 140)},		//przywory
 {IPAddress(192, 168, 43, 1), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 43, 140)},		//telefon
 {IPAddress(192, 168, 0, 100), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 1, 140)},		//Trojdena
 {IPAddress(192, 168, 0, 0), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 1, 0)},			//Trojdena
};
String http_host = "home-master-server.herokuapp.com";
uint16_t http_port = 8080;
String http_uri = "/api/sensor/recordsPack";
String http_url ="http://"+ http_host + http_uri;

void setup() {
	Serial.begin(115200);
	wifiConnector.connect(adresses, staticIps);
	dht.setup(DHT11_PIN, DHTTYPE);
}

StaticJsonDocument<JSON_ARRAY_SIZE(16)> doc;

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

void loop() {   
	if(http.begin(wifiConnector.client, http_url)) {
		http.addHeader("Content-Type", "application/json");
		String msg = getResourcesReprtJsonMsg();
		
		int httpCode = http.POST(msg); 
		String payload = http.getString(); 
		http.end();

		Serial.println(String(" Code: ") + httpCode + ": " + payload); 
		Serial.println(msg);
	}
	wait(1000*60*0.5);
}

String getResourcesReprtJsonMsg() {
	int waterSensor = analogRead(A0);
	int temperature = dht.getTemperature();
	int humidity = dht.getHumidity();
	int computeHeatIndex = dht.computeHeatIndex(temperature, humidity, false);
	JsonArray array = jsonArray(); 
	array = jsonArrayPopulate(array, "sensor", 1, "value", String(waterSensor));
	array = jsonArrayPopulate(array, "sensor", 2, "value", String(temperature));
	array = jsonArrayPopulate(array, "sensor", 3, "value", String(humidity));
	return jsonArraySerialize();
}