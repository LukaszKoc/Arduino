// // On ESP8266:
// // At 80MHz runs up 57600ps, and at 160MHz CPU frequency up to 115200bps with only negligible errors.
// // Connect pin 12 to 14.

// #include "PinsNodeMCU.h"
// #include <SerialLink.h>

// #if defined(ESP8266) && !defined(D5)
// #define D5 (14)
// #define D6 (12)
// #define D7 (13)
// #define D8 (15)
// #endif

// #ifdef ESP32
// #define BAUD_RATE 9600
// #else
// #define BAUD_RATE 9600
// #endif

// // Reminder: the buffer size optimizations here, in particular the isrBufSize that only accommodates
// // a single 8N1 word, are on the basis that any char written to the loopback SoftwareSerial adapter gets read
// // before another write is performed. Block writes with a size greater than 1 would usually fail. 
// SerialLink serialLink;

// void setup() {
//   Serial.begin(115200);
//   serialLink.setup();

//   Serial.println("\nSoftware serial test started");

//   // for (char ch = ' '; ch <= 'z'; ch++) {
//     serialLink.write("Software serial test started");
//   // }
//   serialLink.write("\n");
// }
// String msg;
// void loop() {
//   msg = serialLink.read();
//   if(msg != "-1") {
//     Serial.println(msg);
//   }
//   serialLink.write("ACK: "+ msg);
//   // while (Serial.available() > 0) {
//   //   serialLink.write(Serial.read());
//   //   yield();
//   // }

// }