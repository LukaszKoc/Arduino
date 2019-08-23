#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#include <DisplayController.ino>
#include <IRController.ino>
#include <Constants.ino>

IRController iRController;
DisplayController displayController;
Constants constants;

void setup() {

}

void loop() {
	String inputCommand = constants.mapIRCode(iRController.readIRInputCode());
}
