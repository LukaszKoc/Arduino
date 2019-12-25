#include <ESP8266HTTPClient.h>
#include <WifiConnector.h>
#include <DHTesp.h>
#include <ArduinoJson.h>
#define DHT11_PIN D6
#define DHTTYPE DHTesp::DHT11 

HTTPClient http;
DHTesp dht;
WifiConnector wifiConnector("");

char* url ="http://192.168.0.169:8080/api/sensor/recordsPack";
char* adresses[][2] = {
 {"FEROmedia_13907", "BorysBestia00"}, 
 {"UPCCF2D79F", "N2nrcsz2fxbb"}, 
 {"UPCB3F388D", "Phhe4m2beyvGe"},
 {"use the route luke", "01234567"},
};

void setup() {
	Serial.begin(115200);
	dht.setup(DHT11_PIN, DHTTYPE);
	wifiConnector.connect(adresses[1][0], adresses[1][1]);
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
  	delay(dht.getMinimumSamplingPeriod());
	int waterSensor = analogRead(A0);
	int temperature = dht.getTemperature();
	int humidity = dht.getHumidity();
	int computeHeatIndex = dht.computeHeatIndex(temperature, humidity, false);
	http.begin(wifiConnector.client, url);
	http.addHeader("Content-Type", "application/json");
	JsonArray array = jsonArray(); 
	array = jsonArrayPopulate(array, "sensor", 1, "value", String(waterSensor));
	array = jsonArrayPopulate(array, "sensor", 2, "value", String(temperature));
	array = jsonArrayPopulate(array, "sensor", 3, "value", String(humidity));
	
	String msg = jsonArraySerialize();
	int httpCode = http.POST(msg); 
	String payload = http.getString(); 

	Serial.println(httpCode); 
	Serial.println(msg); 
	http.end();

	delay(100);
}
