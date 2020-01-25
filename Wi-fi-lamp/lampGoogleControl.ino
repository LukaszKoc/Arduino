/***************************************************

 ****************************************************/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "UPCCF2D79F"
#define WLAN_PASS       "N2nrcsz2fxbb"

/************************* Gbridge Setup *********************************/

#define AIO_SERVER      "mqtt.gbridge.io"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "gbridge-u4824"
#define AIO_KEY         "lampka123"

char outputState = 0;
char lastState = 0;

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

Adafruit_MQTT_Publish onoffset = Adafruit_MQTT_Publish(&mqtt, "gBridge/u4824/d15896/onoff/set"); //Replace by your feedname
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, "gBridge/u4824/d15896/onoff"); //Replace by your feedname

/*************************** Sketch Code ************************************/
#define LAMP_OUT_PIN 4
#define LAMP_IN_PIN 5
// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Controle de lampe - Google Home"));

  pinMode(LAMP_OUT_PIN, OUTPUT);     // Initialize the LAMP_OUT_PIN pin as an output
  digitalWrite(LAMP_OUT_PIN, HIGH);
  pinMode(LAMP_IN_PIN, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(LAMP_IN_PIN), handleInterrupt, FALLING);
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  
  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffbutton);
}

uint32_t x=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();
  
  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(3000))) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton.lastread);
      if (strcmp((char *)onoffbutton.lastread, "1") == 0) {
        digitalWrite(LAMP_OUT_PIN, LOW); 
        outputState = 1;
      }
      if (strcmp((char *)onoffbutton.lastread, "0") == 0) {
        digitalWrite(LAMP_OUT_PIN, HIGH);
        outputState = 0;
      }
    }

  }
  
  // Now we can publish stuff!
  if (outputState != lastState) {
    lastState = outputState;
    Serial.print(F("\nSending state val "));
    Serial.print(outputState, BIN);
    Serial.print("...");
    if (! onoffset.publish(outputState)) {
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("OK!"));
    }
  }

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
/*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
}

void handleInterrupt() {
 static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200) 
 {
  if (outputState == 0) {
    outputState = 1;
    digitalWrite(LAMP_OUT_PIN, LOW);
  }
  else {
    outputState = 0;
    digitalWrite(LAMP_OUT_PIN, HIGH);
  }
   }
 last_interrupt_time = interrupt_time;
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
