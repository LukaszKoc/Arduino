// On ESP8266:
// At 80MHz runs up 57600ps, and at 160MHz CPU frequency up to 115200bps with only negligible errors.
// Connect pin 12 to 14.

#include <SoftwareSerial.h>

#if defined(ESP8266) && !defined(D5)
#define D5 (14)
#define D6 (12)
#define D7 (13)
#define D8 (15)
#endif

#define BAUD_RATE 9600

// Reminder: the buffer size optimizations here, in particular the isrBufSize that only accommodates
// a single 8N1 word, are on the basis that any char written to the loopback SoftwareSerial adapter gets read
// before another write is performed. Block writes with a size greater than 1 would usually fail. 
SoftwareSerial serialToRemote;

void setup() {
  Serial.begin(115200);
  serialToRemote.begin(BAUD_RATE, SWSERIAL_8N1, D5, D6, false, 95, 11);

  Serial.println("\nSoftware serial test started");
}

void loop() {
  while (serialToRemote.available() > 0) {
    Serial.write(serialToRemote.read());
    delay(1);
    yield();
  }
}