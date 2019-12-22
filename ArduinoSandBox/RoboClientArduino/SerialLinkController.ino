
#ifndef SerialLinkController_h
#define SerialLinkController_h 
#include "Arduino.h"

SoftwareSerial espSerial(RX_PIN, TX_PIN);
int MSG_LABELS_COUNT = 2;
String MSG_LABELS[] = {"SPEED", "DIRECTIONS"};

class SerialLinkController {
  private:
    void readMessageData(String msg, int &x, int &y);
    int find(String arr[], String value);
  public:
    void readMessage(int &x, int &y);
    void writeMessage(String message);
    void writeCurrentSpeed(float speedL, float speedR);
    String midString(String str, String start, String finish);
}; 

void SerialLinkController::readMessage(int &x, int &y) {
  String msg = espSerial.readString();
  switch (find(MSG_LABELS, midString(msg, "[", ":"))) {
  case 0: //SPEED
    readMessageData(msg, x, y);
    break;
  case 1: //DIRECTIONS 
    readMessageData(msg, x, y);
    break;
  default:
    Serial.println("Invalid message type: " + midString(msg, "[", ":"));
    break;
  }
}
void SerialLinkController::readMessageData(String msg, int &x, int &y) {
  x = midString(msg, ":", ";").toInt();
  y = midString(msg, ":", ".").toInt();
}

void SerialLinkController::writeCurrentSpeed(float speedL, float speedR) {
    String msg = String("{SPEED:") + speedL + ";" + speedR+ "}";
    writeMessage(msg);
}

void SerialLinkController::writeMessage(String message) {
    Serial.write(message);
}

String SerialLinkController::midString(String str, String start, String finish) {
  int locStart = str.indexOf(start);
  if (locStart == -1) return "";
  locStart += start.length();
  int locFinish = str.indexOf(finish, locStart);
  if (locFinish == -1) return "";
  return str.substring(locStart, locFinish);
}

int SerialLinkController::find(String arr[], String value) {
  for (int i=0; i < MSG_LABELS_COUNT; i++) {
     if (value = arr[i]) {
       return i;
     }
  }
  return -1;
}

#endif