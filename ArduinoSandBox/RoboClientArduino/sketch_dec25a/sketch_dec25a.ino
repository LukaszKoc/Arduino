
#include <XBee.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11);
XBee xbee = XBee();
uint8_t send_buffer[2];
XBeeAddress64 addr64 = XBeeAddress64(0x00000000, 0x0000ffff);
ZBTxRequest zbTx;

void setup() {
  send_buffer[0] = 1;
  send_buffer[1] = 2;
  zbTx = ZBTxRequest(addr64, send_buffer, 2);
  Serial.begin(115200);
  mySerial.begin(9600);
  xbee.setSerial(mySerial);
}

void loop() {
  xbee.send(zbTx);
  delay(1000);
}
